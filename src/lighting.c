/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:18:04 by athonda           #+#    #+#             */
/*   Updated: 2025/01/18 21:33:20 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	diffuse(t_rt *p, int x, int y)
{
	t_vec3		l;
	double		dotproduct;
	t_fcolor	kdif;

	if (p->nearest_object[x][y] == PLANE)
		kdif = p->pl.material.kdif;
	else if (p->nearest_object[x][y] == SPHERE)
		kdif = p->sp.material.kdif;
	else if (p->nearest_object[x][y] == CYLINDER)
		kdif = p->cy.material.kdif;
	else
		return ;
	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(kdif, p->l.intensity), dotproduct);
}

void	specular(t_rt *p, int x, int y)
{
	t_vec3		l;
	t_vec3		v;
	t_vec3		r;
	t_fcolor	kspe;

	if (p->nearest_object[x][y] == PLANE)
		kspe = p->pl.material.kspe;
	else if (p->nearest_object[x][y] == SPHERE)
		kspe = p->sp.material.kspe;
	else if (p->nearest_object[x][y] == CYLINDER)
		kspe = p->cy.material.kspe;
	else
		return ;
	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(kspe, p->l.intensity), \
								pow(vec3_dot(v, r), SHINE));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

void	shadow(t_rt *p, int i)
{
	double			light_distance;
	t_intersection	tmp;
	t_ray			ray;

	p->yes_shadow = false;
	p->pi2l = vec3_sub(p->l.position, p->pi);
	p->shadow_start = vec3_add(p->pi, \
							vec3_mult(vec3_normalize(p->pi2l), DELTA));
	p->shadow_direction = vec3_normalize(p->pi2l);
	light_distance = vec3_mag(p->pi2l) - DELTA;
	ray.direction = p->shadow_direction;
	ray.start = p->shadow_start;
	while (++i < 4)
	{
		if (i == 1)
			tmp = quadratic_formula(p, ray);
		else if (i == 2)
			tmp = cylinder_formula(p, ray);
		else if (i == 3)
			tmp = liner_equation(p, ray);
		if (tmp.yes_intersection == true && tmp.solution >= 0 \
			&& tmp.solution <= light_distance)
			p->yes_shadow = true;
	}
}
