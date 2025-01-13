/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/13 10:45:26 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	screen(t_rt *p, double x, double y)
{
	double	converted_x;
	double	converted_y;
	t_vec3	vec_x;
	t_vec3	vec_y;

	converted_x = x - p->win_x / 2;
	converted_y = -y + p->win_y / 2;
	vec_x = vec3_mult(p->c.x_basis, converted_x);
	vec_y = vec3_mult(p->c.y_basis, converted_y);
	p->ray_direction = vec3_normalize(vec3_add(p->c.d_center, vec3_add(vec_x, vec_y)));
	p->ray_start = p->c.position;
}

void	quadratic_formula(t_rt *p)
{
	double	a;
	double	b;
	double	c;

	p->sp2c = vec3_sub(p->c.position, p->sp.center);
	a = vec3_mag(p->ray_direction) * vec3_mag(p->ray_direction);
	b = 2 * vec3_dot(p->sp2c, p->ray_direction);
	c = vec3_dot(p->sp2c, p->sp2c) - p->sp.radius * p->sp.radius;
	p->discriminant = b * b - 4 * a * c;
	p->solution = (-b -sqrt(p->discriminant)) / (2 * a);
	p->pi = vec3_add(p->ray_start, vec3_mult(p->ray_direction, p->solution));
	p->ni = vec3_normalize(vec3_sub(p->pi, p->sp.center));
}

void	diffuse(t_rt *p)
{
	t_vec3	l;
	double	dotproduct;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(p->sp.material.kdif, p->l.intensity), dotproduct);
}

void	specular(t_rt *p)
{
	t_vec3	l;
	t_vec3	v;
	t_vec3	r;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(p->sp.material.kspe, p->l.intensity), pow(vec3_dot(v, r), p->sp.material.shine));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

int	color(t_rt *p)
{
	int	red;
	int	green;
	int	blue;
	int	rgb;

	red = (int)(255 * (p->r_a.red + p->r_d.red + p->r_s.red));
	green = (int)(255 * (p->r_a.green + p->r_d.green + p->r_s.green));
	blue = (int)(255 * (p->r_a.blue + p->r_d.blue + p->r_s.blue));
	rgb = (red << 16) + (green << 8) + (blue);
	return (rgb);
}

int	raytracing(t_rt *p)
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
			quadratic_formula(p);
			if (p->discriminant >= 0)
			{
				if (p->solution < 0)
					continue ;
				diffuse(p);
				specular(p);
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