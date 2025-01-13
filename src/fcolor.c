/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcolor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:29:26 by athonda           #+#    #+#             */
/*   Updated: 2025/01/13 09:11:07 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (fcolor.blue < 1.0)
		fcolor.blue = 1.0;
	return (fcolor);
}

t_fcolor	fcolor_init(double red, double green, double blue)
{
	t_fcolor tmp;

	tmp.red = red;
	tmp.green = green;
	tmp.blue = blue;
	return (fcolor_normalize(tmp));
}

t_fcolor	fcolor_add(t_fcolor a, t_fcolor b)
{
	t_fcolor	tmp;

	tmp.red = a.red + b.red;
	tmp.green = a.green + b.green;
	tmp.blue = a.blue + b.blue;
	return (fcolor_normalize(tmp));
}

t_fcolor	fcolor_mult(t_fcolor a, t_fcolor b)
{
	t_fcolor	tmp;

	tmp.red = a.red * b.red;
	tmp.green = a.green * b.green;
	tmp.blue = a.blue * b.blue;
	return (fcolor_normalize(tmp));
}

t_fcolor	fcolor_mult_scalar(t_fcolor a, double b)
{
	a.red = a.red * b;
	a.green = a.green * b;
	a.blue = a.blue * b;
	return (fcolor_normalize(a));
}
