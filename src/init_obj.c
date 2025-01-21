/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/20 21:36:58 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_sp(char **e, t_object *obj)
{
	t_fcolor	k;

	obj->type = SPHERE;
	init_vec3(e[1], &obj->center);
	obj->radius = ft_atof(e[2]);
	init_rgb(e[3], &k);
	obj->material.kdif = fcolor_init(k.red / 255, k.green / 255, k.blue / 255);
	obj->material.kspe = fcolor_init(0.9, 0.9, 0.9);
	obj->material.shine = 80;
}

void	init_pl(char **e, t_object *obj)
{
	t_fcolor	k;

	obj->type = PLANE;
	init_vec3(e[1], &obj->center);
	init_vec3(e[2], &obj->normal);
	obj->normal = vec3_normalize(obj->normal);
	init_rgb(e[3], &k);
	obj->material.kdif = fcolor_init(k.red / 255, k.green / 255, k.blue / 255);
	obj->material.kspe = fcolor_init(1.0, 1.0, 1.0);
	obj->material.shine = 100;
}

void	init_cy(char **e, t_object *obj)
{
	t_fcolor	k;

	obj->type = CYLINDER;
	init_vec3(e[1], &obj->center);
	init_vec3(e[2], &obj->normal);
	obj->normal = vec3_normalize(obj->normal);
	obj->radius = ft_atof(e[3]) / 2;
	obj->height = ft_atof(e[4]);
	init_rgb(e[5], &k);
	obj->material.kdif = fcolor_init(k.red / 255, k.green / 255, k.blue / 255);
	obj->material.kspe = fcolor_init(0.9, 0.9, 0.9);
	obj->material.shine = 100;
}

int	init_obj(char **e, t_rt *p)
{
	static int	i = -1;

	p->obj[++i] = malloc(sizeof(t_object));
	if (!p->obj[i])
	{
		while (i--)
			free(p->obj[i]);
		free(p->obj);
		return (ft_dprintf(2, "Failed to malloc obj[i]\n"), 1);
	}
	if (!ft_strncmp(*e, "sp", 3))
		init_sp(e, p->obj[i]);
	else if (!ft_strncmp(*e, "pl", 3))
		init_pl(e, p->obj[i]);
	else if (!ft_strncmp(*e, "cy", 3))
		init_cy(e, p->obj[i]);
	return (0);
}
