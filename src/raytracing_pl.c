/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_pl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/13 15:23:41 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	liner_equation(t_rt *p)
{
	double	denominator;
	double	numerator;

	p->pl2c = vec3_sub(p->c.position, p->pl.center);
	denominator = vec3_dot(vec3_mult(p->ray_direction, -1), p->pl.normal);
	numerator = vec3_dot(p->pl2c, p->pl.normal);
	p->solution = numerator / denominator;
	p->pi = vec3_add(p->ray_start, vec3_mult(p->ray_direction, p->solution));
	if (denominator > 0)
		p->ni = p->pl.normal;
	else
		p->ni = vec3_mult(p->pl.normal, -1);
}

void	diffuse_pl(t_rt *p)
{
	t_vec3	l;
	double	dotproduct;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(p->pl.material.kdif, p->l.intensity), dotproduct);
}

void	specular_pl(t_rt *p)
{
	t_vec3	l;
	t_vec3	v;
	t_vec3	r;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(p->pl.material.kspe, p->l.intensity), pow(vec3_dot(v, r), p->pl.material.shine));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

int	raytracing_pl(t_rt *p)
{
	double	x;
	double	y;
	int		offset;

	x = -1;
	while (++x < p->win_x)
	{
		y = -1;
		while (++y < p->win_y)
		{
			screen(p, x, y);
			liner_equation(p);
			if (p->discriminant >= 0)
			{
				if (p->solution < 0)
					continue ;
				diffuse_pl(p);
				specular_pl(p);

				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = color(p);
			}
			else
			{
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = (128 << 24) | 0x00FFFFFF;
			}
		}
	}
	return (0);
}