/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/09 23:08:07 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_element(char **e)
{
	int	error_code;

	error_code = 0;
	if (!ft_strncmp(e[0], "A", 2) || !ft_strncmp(e[0], "C", 2)
		|| !ft_strncmp(e[0], "L", 2))
		error_code = validate_acl(e);
//	else if (!ft_strncmp(e[0], "pl", 3) || !ft_strncmp(e[0], "sp", 3) || !ft_strncmp(e[0], "cy", 3))
//		error_code = validate_object(e);
	else
		return (ft_dprintf(2, "Error\nInvalid element identifier\n"), 1);
	return (error_code);
}

int	validate_file(char *rt)
{
	int		fd;
	char	*line;
	char	**element;

	fd = open(rt, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		if (*line == '\n')
			continue ;
		element = ft_split(line, ' ');
		if (!element)
			return (ft_dprintf(2, "ft_split fail\n"), free(line), 1);
		free(line);
		if (check_element(element))
			return (ft_free_array(element), 1);
		ft_free_array(element);
	}
	if (close(fd) == -1)
		return (perror("Error\n"), 1);
	return (0);
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
