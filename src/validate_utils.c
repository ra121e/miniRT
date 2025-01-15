/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:48:20 by xlok              #+#    #+#             */
/*   Updated: 2025/01/10 18:50:06 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_rgb(char *str)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (dprintf(2, "ft_split fail\n"), 1);
	i = -1;
	while (rgb[++i])
		if (ft_strlen(rgb[i]) > 3 || !is_int(rgb[i])
			|| ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (ft_free_array(rgb), 1);
	if (i != 3)
		return (ft_free_array(rgb), 1);
	return (ft_free_array(rgb), 0);
}

int	validate_vec3(char *str, double min, double max)
{
	char	**vec3;
	int		i;

	vec3 = ft_split(str, ',');
	if (!vec3)
		return (dprintf(2, "ft_split fail\n"), 1);
	i = -1;
	while (vec3[++i])
		if (!is_double(vec3[i])
			|| ft_atof(vec3[i]) < min || ft_atof(vec3[i]) > max)
			return (ft_free_array(vec3), 1);
	if (i != 3)
		return (ft_free_array(vec3), 1);
	return (ft_free_array(vec3), 0);
}
