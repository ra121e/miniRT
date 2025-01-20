/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:02:15 by athonda           #+#    #+#             */
/*   Updated: 2025/01/20 21:16:27 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	assign_sp(t_rt *p, int i)
{
	p->sp.type = SPHERE;
	p->sp.center = p->obj[i]->center;
	p->sp.radius = p->obj[i]->radius;
	p->sp.material.kdif = p->obj[i]->material.kdif;
	p->sp.material.kspe = p->obj[i]->material.kspe;
	p->sp.material.shine = p->obj[i]->material.shine;
//	init_vec3(e[1], &p->sp.center);
//	p->sp.radius = ft_atof(e[2]);
//	init_rgb(e[3], &p->sp.material.kdif);
//	p->sp.material.kspe = fcolor_init(0.9, 0.9, 0.9);
//	p->sp.material.shine = 80;
}

void	assign_pl(t_rt *p, int i)
{
	p->pl.type = PLANE;
	p->pl.center = p->obj[i]->center;
	p->pl.normal = p->obj[i]->normal;
	p->pl.material.kdif = p->obj[i]->material.kdif;
	p->pl.material.kspe = p->obj[i]->material.kspe;
	p->pl.material.shine = p->obj[i]->material.shine;
//	init_vec3(e[1], &p->pl.center);
//	init_vec3(e[2], &p->pl.normal);
//	p->pl.normal = vec3_normalize(p->pl.normal);
//	init_rgb(e[3], &p->pl.material.kdif);
//	p->pl.material.kspe = fcolor_init(1.0, 1.0, 1.0);
//	p->pl.material.shine = 100;
}

void	assign_cy(t_rt *p, int i)
{
	p->cy.type = p->obj[i]->type;
	p->cy.center = p->obj[i]->center;
	p->cy.normal = p->obj[i]->normal;
	p->cy.normal = vec3_normalize(p->cy.normal);
	p->cy.radius = p->obj[i]->radius;
	p->cy.height = p->obj[i]->height;
	p->cy.material.kdif = p->obj[i]->material.kdif;
	p->cy.material.kspe = p->obj[i]->material.kspe;
	p->cy.material.shine = p->obj[i]->material.shine;
//	p->cy.type = CYLINDER;
//	init_vec3(e[1], &p->cy.center);
//	init_vec3(e[2], &p->cy.normal);
//	p->cy.normal = vec3_normalize(p->cy.normal);
//	p->cy.radius = ft_atof(e[3]) / 2;
//	p->cy.height = ft_atof(e[4]);
//	init_rgb(e[5], &p->cy.material.kdif);
//	p->cy.material.kspe = fcolor_init(0.9, 0.9, 0.9);
//	p->cy.material.shine = 100;
}

void	assign_obj(t_rt *p, int i)
{
	if (p->obj[i]->type == SPHERE)
		assign_sp(p, i);
	else if (p->obj[i]->type == PLANE)
		assign_pl(p, i);
	else if (p->obj[i]->type == CYLINDER)
		assign_cy(p, i);
}
