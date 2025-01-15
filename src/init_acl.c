/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_acl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/15 22:03:05 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_a(char **e, t_rt *p)
{
	p->r_a = fcolor_mult_scalar(fcolor_init(255, 255, 255), ft_atof(e[1]));
//	p->a.intensity = ft_atof(e[1]);
//	init_rgb(e[2], &p->a.color);
	return (0);
}

int	init_c(char **e, t_rt *p)
{
	init_vec3(e[1], &p->c.position);
	init_vec3(e[2], &p->c.orientation);
	p->c.fov = deg2rad(ft_atoi(e[3]));
	p->c.distance = p->win_x / 2 / tan(p->c.fov / 2);
	p->c.d_center = vec3_mult(p->c.orientation, p->c.distance);
	p->c.x_basis.x = p->c.d_center.z / sqrt(p->c.d_center.z
			* p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.x_basis.y = 0;
	p->c.x_basis.z = -p->c.d_center.x / sqrt(p->c.d_center.z
			* p->c.d_center.z + p->c.d_center.x * p->c.d_center.x);
	p->c.y_basis = vec3_normalize(vec3_cross(p->c.x_basis,
				vec3_mult(p->c.d_center, -1)));
	return (0);
}

int	init_l(char **e, t_rt *p)
{
	init_vec3(e[1], &p->l.position);
	p->l.intensity = fcolor_mult_scalar(
			fcolor_rgb_convert(255, 255, 255), ft_atof(e[2]));
//	p->l.intensity = ft_atof(e[2]);
	return (0);
}

int	init_acl(char **e, t_rt *p)
{
	if (!ft_strncmp(*e, "A", 2))
		return (init_a(e, p));
	if (!ft_strncmp(*e, "C", 2))
		return (init_c(e, p));
	else if (!ft_strncmp(*e, "L", 2))
		return (init_l(e, p));
	return (0);
}
