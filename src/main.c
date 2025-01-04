/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:31:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/04 19:10:36 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt	*p;

	if (argc != 2)
		exit(1);
	p = malloc(sizeof(t_rt));
	if (!p)
	{
		ft_dprintf(2, "Failed to malloc p\n");
		exit(1);
	}
	(void)argv;
//	p_init(p, argv[1]);
	p->mlx = mlx_init();
//	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, p->title);
//	render(p);
//	mlx_hook(p->win, DestroyNotify, NoEventMask, close_win, p);
//	mlx_hook(p->win, KeyPress, KeyPressMask, handler_key, p);
	mlx_loop(p->mlx);
	return (0);
}
