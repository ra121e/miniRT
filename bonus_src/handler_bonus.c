/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:28:37 by xlok              #+#    #+#             */
/*   Updated: 2025/01/21 19:59:53 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	close_win(void *param)
{
	t_rt	*p;

	p = param;
	ft_free_obj(p, p->nb_obj);
	mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	free(p);
	exit(0);
}

int	handler_key(int keycode, void *param)
{
	t_rt	*p;

	p = param;
	if (keycode == XK_Escape)
		close_win(p);
	else if (keycode == XK_a || keycode == XK_Left)
		move_camera(p, vec3_init(-1, 0, 0));
	else if (keycode == XK_w || keycode == XK_Up)
		move_camera(p, vec3_init(0, 1, 0));
	else if (keycode == XK_d || keycode == XK_Right)
		move_camera(p, vec3_init(1, 0, 0));
	else if (keycode == XK_s || keycode == XK_Down)
		move_camera(p, vec3_init(0, -1, 0));
	else if (keycode == XK_Page_Up)
		move_camera(p, vec3_init(0, 0, 1));
	else if (keycode == XK_Page_Down)
		move_camera(p, vec3_init(0, 0, -1));
	return (0);
}
