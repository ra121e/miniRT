/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:28:37 by xlok              #+#    #+#             */
/*   Updated: 2025/01/11 17:37:47 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	close_win(void *param)
{
	t_rt	*p;

	p = param;
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
//	else if (p->finish == 1)
//		return (0);
//	else if (keycode == XK_a || keycode == XK_Left)
//		movement(p, keycode);
//	else if (keycode == XK_w || keycode == XK_Up)
//		movement(p, keycode);
//	else if (keycode == XK_d || keycode == XK_Right)
//		movement(p, keycode);
//	else if (keycode == XK_s || keycode == XK_Down)
//		movement(p, keycode);
	return (0);
}
