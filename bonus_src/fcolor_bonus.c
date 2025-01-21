/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcolor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:29:26 by athonda           #+#    #+#             */
/*   Updated: 2025/01/21 19:59:50 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

t_fcolor	fcolor_rgb_convert(double r, double g, double b)
{
	return (fcolor_normalize(fcolor_init(r / 255, g / 255, b / 255)));
}
