/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:31:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 20:00:01 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	main(int argc, char **argv)
{
	t_rt	*p;
	t_vec3	acl;
	int		obj_num;

	if (argc != 2 || input_validation(argv[1], &acl, &obj_num))
		exit(1);
	p = malloc(sizeof(t_rt));
	if (!p)
	{
		ft_dprintf(2, "Failed to malloc struct\n");
		exit(1);
	}
	p->nb_obj = obj_num;
	init(p, argv[1]);
	raytracing(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
	mlx_hook(p->win, DestroyNotify, NoEventMask, close_win, p);
	mlx_hook(p->win, KeyPress, KeyPressMask, handler_key, p);
	mlx_loop(p->mlx);
	return (0);
}
