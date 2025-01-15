/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:20:24 by xlok              #+#    #+#             */
/*   Updated: 2025/01/15 17:47:22 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//void	matrix_projection()
//{
//}
//
void	init_value(t_rt *p)
{
	int	i;
	int	j;

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
	i = -1;
	while (++i < 800)
	{
		j= -1;
		while (++j < 800)
		{
			p->nearest[i][j] = INFINITY;
			p->nearest_object[i][j] = NONE;
		}
	}
}

void	init_camera(t_rt *p)
{
	// these values will be from rt file
	p->c.position = vec3_init(0, 4, -5);
	p->c.orientation = vec3_init(0, -0.5, 1);
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
	p->sp.center = vec3_init(0, -2, 3);
	p->sp.radius = 2;
	p->sp.material.kdif = fcolor_rgb_convert(0, 0, 255);
	p->sp.material.kspe = fcolor_init(0.9, 0.9, 0.9);
	p->sp.material.shine = 80;
}

void	init_plane(t_rt *p)
{
	p->pl.type = PLANE;
	p->pl.center = vec3_init(0, -2, 0);
	p->pl.normal = vec3_normalize(vec3_init(0, 1, 0));
	p->pl.material.kdif = fcolor_rgb_convert(0, 255, 0);
	p->pl.material.kspe = fcolor_init(1.0, 1.0, 1.0);
	p->pl.material.shine = 100;
}

void	init_cylinder(t_rt *p)
{
	p->cy.type = CYLINDER;
	p->cy.center = vec3_init(2, 0, 0);
	p->cy.normal = vec3_normalize(vec3_init(-1, 1, 1));
	p->cy.radius = 0.3;
	p->cy.height = 10;
	p->cy.material.kdif = fcolor_rgb_convert(255, 0, 0);
	p->cy.material.kspe = fcolor_init(0.9, 0.9, 0.9);
	p->cy.material.shine = 100;
}

void	init_light(t_rt *p)
{
	p->l.intensity = fcolor_mult_scalar(fcolor_rgb_convert(255, 255, 255), 0.7);
	p->l.position = vec3_init(50, 50, -50);
}

void	init_ambient(t_rt *p)
{
	p->r_a = fcolor_mult_scalar(fcolor_init(255, 255, 255), 0.2);
}

int	init(t_rt *p)
{
//	matrix_projection();
	init_value(p);
	init_camera(p);
	init_sphere(p);
	init_plane(p);
	init_cylinder(p);
	init_ambient(p);
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
