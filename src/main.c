/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:31:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/18 16:33:43 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt		*p;

	if (argc != 2 || input_validation(argv[1]))
		exit(1);
	p = malloc(sizeof(t_rt));
	if (!p)
	{
		ft_dprintf(2, "Failed to malloc struct\n");
		exit(1);
	}
	init(p, argv[1]);
	raytracing(p);
	mlx_hook(p->win, DestroyNotify, NoEventMask, close_win, p);
	mlx_hook(p->win, KeyPress, KeyPressMask, handler_key, p);
	mlx_loop(p->mlx);
	return (0);
}
