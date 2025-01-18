/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcolor_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:04:10 by athonda           #+#    #+#             */
/*   Updated: 2025/01/18 12:06:22 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_fcolor	fcolor_normalize(t_fcolor fcolor)
{
	if (fcolor.red < 0)
		fcolor.red = 0.0;
	if (fcolor.green < 0)
		fcolor.green = 0.0;
	if (fcolor.blue < 0)
		fcolor.blue = 0.0;
	if (fcolor.red > 1.0)
		fcolor.red = 1.0;
	if (fcolor.green > 1.0)
		fcolor.green = 1.0;
	if (fcolor.blue > 1.0)
		fcolor.blue = 1.0;
	return (fcolor);
}

t_fcolor	fcolor_init(double red, double green, double blue)
{
	t_fcolor	tmp;

	tmp.red = red;
	tmp.green = green;
	tmp.blue = blue;
	return (fcolor_normalize(tmp));
}
