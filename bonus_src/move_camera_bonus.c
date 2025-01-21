/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:30:41 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 20:00:03 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
