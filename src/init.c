/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:20:24 by xlok              #+#    #+#             */
/*   Updated: 2025/01/04 19:27:24 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//void	matrix_projection()
//{
//}
//
void	init_value(t_rt *p)
{
	p->win_x = 800;
	p->win_y = 800;
	p->title = "miniRT";
}

void	init(t_rt *p)
{
//	matrix_projection();
	init_value(p);
}
