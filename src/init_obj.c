/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/11 18:03:19 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_sp(char **e, t_rt *p)
{
	p->sp.type = SPHERE;
	init_vec3(e[1], &p->sp.center);
	p->sp.radius = ft_atof(e[2]);
	init_rgb(e[3], &p->sp.material.kdif);
	return (0);
}

int	init_pl(char **e, t_rt *p)
{
	p->pl.type = PLANE;
	init_vec3(e[1], &p->pl.center);
	init_vec3(e[2], &p->pl.normal);
	init_rgb(e[3], &p->pl.material.kdif);
	return (0);
}

int	init_cy(char **e, t_rt *p)
{
	p->cy.type = CYLINDER;
	init_vec3(e[1], &p->cy.center);
	init_vec3(e[2], &p->cy.normal);
	p->cy.diameter = ft_atof(e[3]);
	p->cy.height = ft_atof(e[4]);
	init_rgb(e[5], &p->cy.material.kdif);
	return (0);
}

int	init_obj(char **e, t_rt *p)
{
	if (!ft_strncmp(*e, "sp", 3))
		return (init_sp(e, p));
	else if (!ft_strncmp(*e, "pl", 3))
		return (init_pl(e, p));
	else if (!ft_strncmp(*e, "cy", 3))
		return (init_cy(e, p));
	return (0);
}
