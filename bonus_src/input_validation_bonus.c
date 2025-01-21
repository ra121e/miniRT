/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 19:59:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	validate_element(char **e, t_vec3 *acl, int *obj_num)
{
	if (!ft_strncmp(e[0], "A", 2) || !ft_strncmp(e[0], "C", 2)
		|| !ft_strncmp(e[0], "L", 2))
		return (validate_acl(e, acl));
	else if (!ft_strncmp(e[0], "pl", 3) || !ft_strncmp(e[0], "sp", 3)
		|| !ft_strncmp(e[0], "cy", 3))
		return (validate_obj(e, obj_num));
	else
		return (ft_dprintf(2, "Error\nInvalid element identifier\n"), 1);
	return (0);
}

static int	loop(int fd, t_vec3 *acl, int *obj_num)
{
	char	*line;
	char	**element;

	while (1)
	{
		line = gnl(fd);
		if (!line)
			return (0);
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		line[ft_strlen(line) - 1] = 0;
		element = ft_split(line, ' ');
		free(line);
		if (!element)
			return (clear_gnl(fd), ft_dprintf(2, "ft_split fail\n"), 1);
		if (validate_element(element, acl, obj_num))
			return (clear_gnl(fd), ft_free_array(element), 1);
		ft_free_array(element);
	}
}

int	validate_file(char *rt, t_vec3 *acl, int *obj_num)
{
	int	fd;
	int	fd_d;
	int	status;

	fd = open(rt, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	fd_d = open(rt, O_DIRECTORY);
	if (fd_d != -1)
	{
		if (close(fd) == -1)
			return (perror("Error\n"), 1);
		if (close(fd_d) == -1)
			return (perror("Error\n"), 1);
		return (ft_dprintf(2, "Error\n.rt is directory\n"), 1);
	}
	status = loop(fd, acl, obj_num);
	if (close(fd) == -1)
		return (perror("Error\n"), 1);
	return (status);
}

int	input_validation(char *arg, t_vec3 *acl, int *obj_num)
{
	if (ft_strlen(arg) < 4
		|| ft_strncmp(arg + ft_strlen(arg) - 3, ".rt", 4)
		|| !ft_isalnum(*arg))
		return (ft_dprintf(2, "Error: "
				"Pls enter a .rt file starting with alphanumeric\n"), 1);
	acl->x = 0;
	acl->y = 0;
	acl->z = 0;
	*obj_num = 0;
	if (validate_file(arg, acl, obj_num))
		return (1);
	if (!acl->x || !acl->y || !acl->z)
		return (printf("Error\nIncomplete acl\n"), 1);
	if (!*obj_num)
		return (printf("Error\nNeed at least 1 object\n"), 1);
	return (0);
}
