/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/08 17:00:44 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	raytracing(t_rt *p)
{
	double	x;
	double	y;
	t_vec3	camera_vec;
	t_vec3	sphere_vec;
	double	sphere_r;
	t_vec3	screen_vec;
	t_vec3	dir_vec;
	t_vec3	camera2sphere_vec;
	double	a;
	double	b;
	double	c;
	double	d;
	int		offset;

	camera_vec = vec3_init(0.5, 0.5, -10);
	sphere_vec = vec3_init(0, 0, 5);
	sphere_r = 1;
	x = -1;
	while (++x < p->win_x)
	{
		y = -1;
		while (++y < p->win_y)
		{
			screen_vec = vec3_init(2 * x / p->win_x - 1.0, 2 * y / p->win_y - 1.0, 0);
			dir_vec = vec3_normalize(vec3_sub(screen_vec, camera_vec));
			camera2sphere_vec = vec3_sub(camera_vec, sphere_vec);
			a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
			b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
			c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - sphere_r * sphere_r;
			d = b * b - 4 * a * c;
			if (d >= 0)
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