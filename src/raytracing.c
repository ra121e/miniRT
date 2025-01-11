/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/11 20:13:04 by xlok             ###   ########.fr       */
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
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = (128 << 24) | 0x000000FF;
			}
			else
			{
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = (128 << 24) | 0x00FF0000;
			}
		}
	}
	return (0);
}
