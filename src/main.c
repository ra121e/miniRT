/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:31:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/14 00:35:19 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt		*p;

	if (argc != 2)
		exit(1);
	p = malloc(sizeof(t_rt));
	if (!p)
	{
		ft_dprintf(2, "Failed to malloc struct\n");
		exit(1);
	}
	(void)argv;
	if (init(p) == 1)
		return (0);
//	p->mlx = mlx_init();
//	p->win = mlx_new_window(p->mlx, p->win_x, p->win_y, p->title);
	printf("after initilize\n");
//	raytracing_pl(p);
	raytracing(p);
	raytracing_cy(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
//	render(p);
	mlx_hook(p->win, DestroyNotify, NoEventMask, close_win, p);
	mlx_hook(p->win, KeyPress, KeyPressMask, handler_key, p);
	mlx_loop(p->mlx);
	return (0);
}
