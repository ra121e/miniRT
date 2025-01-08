/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:20:24 by xlok              #+#    #+#             */
/*   Updated: 2025/01/08 22:04:20 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_element(char **e)
{
	while (*e)
	{
		if (ft_strlen(*e) > 2)
		{
			if ((ft_strlen(*e) == 1 && (ft_strncmp(*e, "A", 2) ||
				ft_strncmp(*e, "C", 2) || ft_strncmp(*e, "L", 2))) ||
				(ft_strlen(*e) == 2 && (ft_strncmp(*e, "pl", 3) ||
				ft_strncmp(*e, "sp", 3) || ft_strncmp(*e, "cy", 3))))
			ft_dprintf(2, "Error\nInvalid element identifier\n");//cleanup
		}
		e++;
	}
}

int	init_file(char *rt)
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
		element = ft_split(line, ' ');
		free(line);
		init_element(element);
		ft_free_array(element);
	}
	if (close(fd) == -1)
		return (perror("Error\n"), 1);
	return (0);
}

void	init_value(t_rt *p)
{
	p->mlx = NULL;
	p->win = NULL;
	p->img = NULL;
	p->addr = NULL;
	p->bpp = 0;
	p->line_size = 0;
	p->endian = 0;
	p->win_x = 800;
	p->win_y = 800;
	p->title = "miniRT";
}

int	init(t_rt *p, char *rt)
{
	if (init_file(rt))
		return (1);
	init_value(p);
	p->mlx = mlx_init();
	if (p->mlx == NULL)
		return (1);
	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, p->title);
	if (p->win == NULL)
		return (1);
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	if (p->img == NULL)
		return (1);
	p->addr = mlx_get_data_addr(p->img, &p->bpp, &p->line_size, &p->endian);
	if (p->addr == NULL)
		return (1);
	return (0);
}
