/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/10 19:15:40 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_sp(char **e)
{
	if (!e[1] || validate_vec3(e[1], XYZ_MIN, XYZ_MAX)
		|| !e[2] || !is_double(e[2]) || ft_atof(e[2]) <= 0
		|| !e[3] || validate_rgb(e[3])
		|| e[4])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_pl(char **e)
{
	if (!e[1] || validate_vec3(e[1], XYZ_MIN, XYZ_MAX)
		|| !e[2] || validate_vec3(e[2], -1, 1)
		|| !e[3] || validate_rgb(e[3])
		|| e[4])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_cy(char **e)
{
	if (!e[1] || validate_vec3(e[1], XYZ_MIN, XYZ_MAX)
		|| !e[2] || validate_vec3(e[2], -1, 1)
		|| !e[3] || !is_double(e[3]) || ft_atof(e[3]) <= 0
		|| !e[4] || !is_double(e[4]) || ft_atof(e[4]) <= 0
		|| !e[5] || validate_rgb(e[5])
		|| e[6])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_obj(char **e)
{
	if (!ft_strncmp(*e, "sp", 3))
		return (validate_sp(e));
	else if (!ft_strncmp(*e, "pl", 3))
		return (validate_pl(e));
	else if (!ft_strncmp(*e, "cy", 3))
		return (validate_cy(e));
	return (0);
}
