/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/20 20:39:31 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_element(char **e, t_rt *p)
{
	if (!ft_strncmp(e[0], "A", 2) || !ft_strncmp(e[0], "C", 2)
		|| !ft_strncmp(e[0], "L", 2))
		init_acl(e, p);
	else if (!ft_strncmp(e[0], "pl", 3) || !ft_strncmp(e[0], "sp", 3)
		|| !ft_strncmp(e[0], "cy", 3))
		init_obj(e, p);
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
		init_element(element, p);
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
