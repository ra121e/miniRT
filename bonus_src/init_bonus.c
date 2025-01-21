/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:20:24 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 19:59:54 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	cleanup(t_rt *p, int status)
{
	if (status >= 2)
	{
		mlx_destroy_display(p->mlx);
		free(p->mlx);
	}
	if (status >= 1)
		free(p);
	exit(status);
}

void	init_nearest(t_rt *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->win_y)
	{
		x = -1;
		while (++x < p->win_x)
		{
			p->nearest[x][y] = INFINITY;
			p->nearest_object[x][y] = NONE;
		}
	}
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
	p->title = "miniRT_bonus";
	p->pi2l.x = 0;
	p->pi2l.y = 0;
	p->pi2l.z = 0;
	p->pi.x = 0;
	p->pi.y = 0;
	p->pi.z = 0;
	init_nearest(p);
}

void	init(t_rt *p, char *rt)
{
	p->obj = malloc(sizeof(t_object) * p->nb_obj);
	if (!p->obj)
	{
		ft_dprintf(2, "Failed to malloc obj\n");
		cleanup(p, 1);
	}
	init_value(p);
	if (init_file(rt, p))
		cleanup(p, 1);
	p->mlx = mlx_init();
	if (!p->mlx)
		cleanup(p, 1);
	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, p->title);
	if (!p->win)
		cleanup(p, 2);
}
