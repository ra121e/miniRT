/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:30:41 by xlok              #+#    #+#             */
/*   Updated: 2025/01/28 10:25:36 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	move_camera(t_rt *p, t_vec3 offset)
{
	t_vec3	up;

	p->c.position = vec3_add(p->c.position, offset);
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	up = vec3_init(0, 1, 0);
	if (fabs(p->c.orientation.y) > 0.9999)
		up = vec3_init(0, 0, 1);
	p->c.x_basis = vec3_normalize(vec3_cross(up, p->c.orientation));
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.orientation, p->c.x_basis));
	init_nearest(p);
	raytracing(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
	return (0);
}

int	turn_camera(t_rt *p, double angle)
{
	t_vec3	up;
	t_vec3	tmp1;
	t_vec3	tmp2;
	t_vec3	tmp3;
	t_vec3	v;
	t_vec3	axis;

	if (p->c.orientation.x != 0)
	{
		v.x = p->c.orientation.z;
		v.y = 0;
		v.z = -p->c.orientation.x;
	}
	else
	{
		v.x = 1.0;
		v.y = 0;
		v.z = 0;
	}
	axis = vec3_normalize(vec3_cross(p->c.orientation, v));
	tmp1 = vec3_mult(p->c.orientation, cos(angle));
	tmp2 = vec3_mult(vec3_cross(axis, p->c.orientation), sin(angle));
	tmp3 = vec3_mult(axis, vec3_dot(axis, p->c.orientation) * (1 - cos(angle)));
	p->c.orientation = vec3_add(vec3_add(tmp1, tmp2), tmp3);
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	up = vec3_init(0, 1, 0);
	if (fabs(p->c.orientation.y) > 0.9999)
		up = vec3_init(0, 0, 1);
	p->c.x_basis = vec3_normalize(vec3_cross(up, p->c.orientation));
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.orientation, p->c.x_basis));
	init_nearest(p);
	raytracing(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
	return (0);
}

int	roll_camera(t_rt *p, double angle)
{
	t_vec3	up;
	t_vec3	tmp1;
	t_vec3	tmp2;
	t_vec3	tmp3;
	t_vec3	v;
	t_vec3	axis;

	if (fabs(p->c.orientation.z) < 1e-6)
	{
		v.x = -p->c.orientation.y;
		v.y = p->c.orientation.x;
		v.z = 0;
	}
	else
	{
		v.x = 0;
		v.y = p->c.orientation.z;
		v.z = -p->c.orientation.y;
	}
	axis = vec3_normalize(vec3_cross(p->c.orientation, v));
	tmp1 = vec3_mult(p->c.orientation, cos(angle));
	tmp2 = vec3_mult(vec3_cross(axis, p->c.orientation), sin(angle));
	tmp3 = vec3_mult(axis, vec3_dot(axis, p->c.orientation) * (1 - cos(angle)));
	p->c.orientation = vec3_add(vec3_add(tmp1, tmp2), tmp3);
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	up = vec3_init(0, 1, 0);
	if (fabs(p->c.orientation.y) > 0.9999)
		up = vec3_init(0, 0, 1);
	p->c.x_basis = vec3_normalize(vec3_cross(up, p->c.orientation));
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.orientation, p->c.x_basis));
	init_nearest(p);
	raytracing(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
	return (0);
}