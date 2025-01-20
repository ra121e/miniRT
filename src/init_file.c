/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/20 21:48:09 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_element(char **e, t_rt *p)
{
	if (!ft_strncmp(e[0], "A", 2) || !ft_strncmp(e[0], "C", 2)
		|| !ft_strncmp(e[0], "L", 2))
		return (init_acl(e, p), 0);
	else if (!ft_strncmp(e[0], "pl", 3) || !ft_strncmp(e[0], "sp", 3)
		|| !ft_strncmp(e[0], "cy", 3))
		return (init_obj(e, p));
	return (0);
}

static int	loop(int fd, t_rt *p)
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
		if (init_element(element, p))
			return (clear_gnl(fd), ft_free_array(element), 1);
		ft_free_array(element);
	}
}

int	init_file(char *rt, t_rt *p)
{
	int	fd;
	int	status;

	fd = open(rt, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	status = loop(fd, p);
	if (close(fd) == -1)
		return (perror("Error\n"), 1);
	return (status);
}
