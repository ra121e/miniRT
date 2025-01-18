/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:17:51 by athonda           #+#    #+#             */
/*   Updated: 2025/01/18 12:23:45 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	color(t_rt *p)
{
	int			red;
	int			green;
	int			blue;
	int			rgb;

	p->r_surface = fcolor_add(p->r_d, p->r_s);
	if (p->yes_shadow == true)
		p->r_surface = fcolor_init(0, 0, 0);
	p->r_all = fcolor_add(p->r_surface, p->r_a);
	red = (int)(255 * p->r_all.red);
	green = (int)(255 * p->r_all.green);
	blue = (int)(255 * p->r_all.blue);
	rgb = (red << 16) + (green << 8) + (blue);
	return (rgb);
}

void	draw(t_rt *p, int x, int y)
{
	int	offset;

	if (p->nearest_object[x][y])
	{
		offset = y * p->line_size + (x * p->bpp / 8);
		*(int *)(p->addr + offset) = color(p);
	}
	else
	{
		offset = y * p->line_size + (x * p->bpp / 8);
		*(int *)(p->addr + offset) = (128 << 24) | 0x00FFFFFF;
	}
}
