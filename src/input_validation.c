/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/11 18:18:53 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_element(char **e)
{
	if (!ft_strncmp(e[0], "A", 2) || !ft_strncmp(e[0], "C", 2)
		|| !ft_strncmp(e[0], "L", 2))
		return (validate_acl(e));
	else if (!ft_strncmp(e[0], "pl", 3) || !ft_strncmp(e[0], "sp", 3)
		|| !ft_strncmp(e[0], "cy", 3))
		return (validate_obj(e));
	else
		return (ft_dprintf(2, "Error\nInvalid element identifier\n"), 1);
	return (0);
}

static int	loop(int fd)
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
			return (ft_dprintf(2, "ft_split fail\n"), 1);
		if (validate_element(element))
			return (ft_free_array(element), 1);
		ft_free_array(element);
	}
}

int	validate_file(char *rt)
{
	int	fd;
	int	status;

	fd = open(rt, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	status = loop(fd);
	if (close(fd) == -1)
		return (perror("Error\n"), 1);
	return (status);
}

int	input_validation(char *arg)
{
	if (ft_strlen(arg) < 4
		|| ft_strncmp(arg + ft_strlen(arg) - 3, ".rt", 4)
		|| !ft_isalnum(*arg))
		return (ft_dprintf(2, "Error: "
				"Pls enter a .rt file starting with alphanumeric\n"), 1);
	if (validate_file(arg))
		return (1);
	return (0);
}
