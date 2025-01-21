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
}

void	assign_pl(t_rt *p, int i)
{
	p->pl.type = PLANE;
	p->pl.center = p->obj[i]->center;
	p->pl.normal = p->obj[i]->normal;
	p->pl.material.kdif = p->obj[i]->material.kdif;
	p->pl.material.kspe = p->obj[i]->material.kspe;
	p->pl.material.shine = p->obj[i]->material.shine;
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
