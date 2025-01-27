/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_acl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:06:58 by xlok              #+#    #+#             */
/*   Updated: 2025/01/20 19:57:47 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_a(char **e, t_vec3 *acl)
{
	if (++acl->x > 1)
		return (ft_dprintf(2, "Error\nCan only have 1 Element %s\n", *e), 1);
	if (!e[1] || !is_double(e[1]) || ft_atof(e[1]) < 0 || ft_atof(e[1]) > 1
		|| !e[2] || validate_rgb(e[2])
		|| e[3])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_c(char **e, t_vec3 *acl)
{
	if (++acl->y > 1)
		return (ft_dprintf(2, "Error\nCan only have 1 Element %s\n", *e), 1);
	if (!e[1] || validate_vec3(e[1], XYZ_MIN, XYZ_MAX)
		|| !e[2] || validate_vec3(e[2], -1, 1)
		|| !e[3] || !is_int(e[3]) || ft_atoi(e[3]) < 0 || ft_atoi(e[3]) > 180
		|| e[4])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_l(char **e, t_vec3 *acl)
{
	if (++acl->z > 1)
		return (ft_dprintf(2, "Error\nCan only have 1 Element %s\n", *e), 1);
	if (!e[1] || validate_vec3(e[1], XYZ_MIN, XYZ_MAX)
		|| !e[2] || !is_double(e[2]) || ft_atof(e[2]) < 0 || ft_atof(e[2]) > 1
		|| e[3])
		return (ft_dprintf(2, "Error\nElement %s invalid values\n", *e), 1);
	return (0);
}

int	validate_acl(char **e, t_vec3 *acl)
{
	if (!ft_strncmp(*e, "A", 2))
		return (validate_a(e, acl));
	else if (!ft_strncmp(*e, "C", 2))
		return (validate_c(e, acl));
	else if (!ft_strncmp(*e, "L", 2))
		return (validate_l(e, acl));
	return (0);
}
