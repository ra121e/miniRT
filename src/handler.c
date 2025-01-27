/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:28:37 by xlok              #+#    #+#             */
/*   Updated: 2025/01/28 10:42:16 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	else if (keycode == XK_Left)
		turn_camera(p, -(M_PI / 36));
	else if (keycode == XK_a)
		turn_camera(p, -(M_PI / 12));
	else if (keycode == XK_Right)
		turn_camera(p, M_PI / 36);
	else if (keycode == XK_d)
		turn_camera(p, M_PI / 12);
	else if (keycode == XK_Up)
		roll_camera(p, -(M_PI / 36));
	else if (keycode == XK_w)
		roll_camera(p, -(M_PI / 12));
	else if (keycode == XK_Down)
		roll_camera(p, M_PI / 36);
	else if (keycode == XK_s)
		roll_camera(p, M_PI / 12);
	else if (keycode == XK_Page_Up)
		move_camera(p, p->c.orientation);
	else if (keycode == XK_Page_Down)
		move_camera(p, vec3_mult(p->c.orientation, -1));
	return (0);
}
