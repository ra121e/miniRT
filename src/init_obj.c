/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/18 21:29:58 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_sp(char **e, t_rt *p)
{
	p->sp.type = SPHERE;
	init_vec3(e[1], &p->sp.center);
	p->sp.radius = ft_atof(e[2]);
	init_rgb(e[3], &p->sp.material.kdif);
	p->sp.material.kspe = fcolor_init(0.9, 0.9, 0.9);
	p->sp.material.shine = 80;
}

void	init_pl(char **e, t_rt *p)
{
	p->pl.type = PLANE;
	init_vec3(e[1], &p->pl.center);
	init_vec3(e[2], &p->pl.normal);
	p->pl.normal = vec3_normalize(p->pl.normal);
	init_rgb(e[3], &p->pl.material.kdif);
	p->pl.material.kspe = fcolor_init(1.0, 1.0, 1.0);
	p->pl.material.shine = 100;
}

void	init_cy(char **e, t_rt *p)
{
	p->cy.type = CYLINDER;
	init_vec3(e[1], &p->cy.center);
	init_vec3(e[2], &p->cy.normal);
	p->cy.normal = vec3_normalize(p->cy.normal);
	p->cy.radius = ft_atof(e[3]) / 2;
	p->cy.height = ft_atof(e[4]);
	init_rgb(e[5], &p->cy.material.kdif);
	p->cy.material.kspe = fcolor_init(0.9, 0.9, 0.9);
	p->cy.material.shine = 100;
}

void	init_obj(char **e, t_rt *p)
{
	if (!ft_strncmp(*e, "sp", 3))
		init_sp(e, p);
	else if (!ft_strncmp(*e, "pl", 3))
		init_pl(e, p);
	else if (!ft_strncmp(*e, "cy", 3))
		init_cy(e, p);
}
