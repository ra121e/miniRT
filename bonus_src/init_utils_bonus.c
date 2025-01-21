/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:21:52 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 19:59:58 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	init_rgb(char *str, t_fcolor *p)
{
	char	**vec3;

	vec3 = ft_split(str, ',');
	if (!vec3)
		return (dprintf(2, "ft_split fail\n"), 1);
	p->red = (double)ft_atoi(vec3[0]);
	p->green = (double)ft_atoi(vec3[1]);
	p->blue = (double)ft_atoi(vec3[2]);
	return (ft_free_array(vec3), 0);
}

int	init_vec3(char *str, t_vec3 *p)
{
	char	**vec3;

	vec3 = ft_split(str, ',');
	if (!vec3)
		return (dprintf(2, "ft_split fail\n"), 1);
	*p = vec3_init(ft_atof(vec3[0]), ft_atof(vec3[1]), ft_atof(vec3[2]));
	return (ft_free_array(vec3), 0);
}
