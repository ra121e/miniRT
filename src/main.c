/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:31:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/08 21:40:51 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt	*p;

	if (argc != 2 || input_validation(argv[1]))
		exit(1);
	p = malloc(sizeof(t_rt));
	if (!p)
	{
		ft_dprintf(2, "Failed to malloc struct\n");
		exit(1);
	}
	if (init(p, argv[1]))
		return (1);//cleanup before exit
	printf("after initilize\n");
	raytracing(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_hook(p->win, DestroyNotify, NoEventMask, close_win, p);
	mlx_hook(p->win, KeyPress, KeyPressMask, handler_key, p);
	mlx_loop(p->mlx);
	return (0);
}
