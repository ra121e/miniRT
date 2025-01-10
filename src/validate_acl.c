/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_acl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/10 08:31:11 by xlok             ###   ########.fr       */
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

int	validate_c(char **e)
{
	static int	c = 0;

	if (++c > 1)
		return (ft_dprintf(2, "Error\nCan only have 1 Element C\n"), 1);
	if (!e[1] || validate_vec3(e[1], -400, 400) //using 800x800 (DEFINE in .h?)
		|| !e[2] || validate_vec3(e[2], -1, 1)
		|| !e[3] || !is_int(e[3]) || ft_atoi(e[3]) < 0 || ft_atoi(e[3]) > 180
		|| e[4])
		return (ft_dprintf(2, "Error\nElement C invalid values\n"), 1);
	return (0);
}

int	validate_l(char **e)
{
	static int	l = 0;

	if (++l > 1)
		return (ft_dprintf(2, "Error\nCan only have 1 Element L\n"), 1);
	if (!e[1] || validate_vec3(e[1], -400, 400) //using 800x800 (DEFINE in .h?)
		|| !e[2] || !is_double(e[2]) || ft_atof(e[2]) < 0 || ft_atof(e[2]) > 1
		|| e[3])
		return (ft_dprintf(2, "Error\nElement L invalid values\n"), 1);
	return (0);
}

int	validate_acl(char **e)
{
	static int	a = 0;

	if (!ft_strncmp(*e, "A", 2))
	{
		if (++a > 1)
			return (ft_dprintf(2, "Error\nCan only have 1 Element A\n"), 1);
		if (!e[1] || !is_double(e[1]) || ft_atof(e[1]) < 0 || ft_atof(e[1]) > 1
			|| !e[2] || validate_rgb(e[2])
			|| e[3])
			return (ft_dprintf(2, "Error\nElement A invalid values\n"), 1);
	}
	else if (!ft_strncmp(*e, "C", 2))
		return (validate_c(e));
	else if (!ft_strncmp(*e, "L", 2))
		return (validate_l(e));
	return (0);
}
