/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:30:41 by xlok              #+#    #+#             */
/*   Updated: 2025/01/16 18:15:04 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	move_camera(t_rt *p, t_vec3 offset)
{
	p->c.position = vec3_add(p->c.position, offset);
//	init_vec3(e[2], &p->c.orientation);
//	p->c.fov = deg2rad(ft_atoi(e[3]));
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	p->c.x_basis.x = p->c.d_center.z / sqrt(p->c.d_center.z
			* p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.x_basis.y = 0;
	p->c.x_basis.z = -p->c.d_center.x / sqrt(p->c.d_center.z
			* p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.x_basis,
				vec3_mult(p->c.d_center, -1)));
	init_nearest(p);
	raytracing(p);
	return (0);
}
