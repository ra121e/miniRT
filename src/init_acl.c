/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_acl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/20 16:52:58 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_a(char **e, t_rt *p)
{
	t_fcolor	rgb;

	if (init_rgb(e[2], &rgb))
		cleanup(p, 1);
	p->r_a = fcolor_mult_scalar(
			fcolor_init(rgb.red / 255, rgb.green / 255, rgb.blue / 255),
			ft_atof(e[1]));
}

void	init_c(char **e, t_rt *p)
{
	t_vec3	up;

	init_vec3(e[1], &p->c.position);
	init_vec3(e[2], &p->c.orientation);
	p->c.fov = deg2rad(ft_atoi(e[3]));
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	up = vec3_init(0, 1, 0);
	if (fabs(p->c.orientation.y) > 0.9999)
		up = vec3_init(0, 0, 1);
	p->c.x_basis = vec3_normalize(vec3_cross(up, p->c.orientation));
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.orientation, p->c.x_basis));
}

void	init_l(char **e, t_rt *p)
{
	init_vec3(e[1], &p->l.position);
	p->l.intensity = fcolor_mult_scalar(
			fcolor_rgb_convert(255, 255, 255), ft_atof(e[2]));
}

void	init_acl(char **e, t_rt *p)
{
	if (!ft_strncmp(*e, "A", 2))
		init_a(e, p);
	else if (!ft_strncmp(*e, "C", 2))
		init_c(e, p);
	else if (!ft_strncmp(*e, "L", 2))
		init_l(e, p);
}
