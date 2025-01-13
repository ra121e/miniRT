/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:20:24 by xlok              #+#    #+#             */
/*   Updated: 2025/01/13 09:13:23 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//void	matrix_projection()
//{
//}
//
void	init_value(t_rt *p)
{
	p->mlx = NULL;
	p->win = NULL;
	p->img = NULL;
	p->addr = NULL;
	p->bpp = 0;
	p->line_size = 0;
	p->endian = 0;
	p->win_x = 800;
	p->win_y = 800;
	p->title = "miniRT";
}

void	init_camera(t_rt *p)
{
	// these values will be from rt file
	p->c.position = vec3_init(0, 0, 0);
	p->c.orientation = vec3_init(0, 0, 1);
	p->c.fov = deg2rad(70);
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);

	p->c.x_basis.x = p->c.d_center.z / sqrt(p->c.d_center.z * p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.x_basis.y = 0;
	p->c.x_basis.z = -p->c.d_center.x / sqrt(p->c.d_center.z * p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.x_basis, vec3_mult(p->c.d_center, -1)));
}

void	init_sphere(t_rt *p)
{
	p->sp.type = SPHERE;
	p->sp.center = vec3_init(0, 0, 20.6);
	p->sp.radius = 6.3;
	p->sp.red = 255;
	p->sp.green = 255;
	p->sp.blue = 255;
}

void	init_light(t_rt *p)
{
	p->l.intensity = 0.9;
	p->l.position = vec3_init(0, 20, -20);
	p->r_a = fcolor_mult_scalar(fcolor_init(255, 255, 255), 0.2);
}

int	init(t_rt *p)
{
//	matrix_projection();
	init_value(p);
	init_camera(p);
	init_sphere(p);
	init_light(p);
	p->mlx = mlx_init();
	if (p->mlx == NULL)
		return (1);
	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, p->title);
	if (p->win == NULL)
		return (1);
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	if (p->img == NULL)
		return (1);
	p->addr = mlx_get_data_addr(p->img, &p->bpp, &p->line_size, &p->endian);
	if (p->addr == NULL)
		return (1);
	return (0);
}
