/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_fnc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:07:48 by athonda           #+#    #+#             */
/*   Updated: 2025/01/21 20:02:59 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double	vec3_mag(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	mag;

	mag = vec3_mag(a);
	return (vec3_init(a.x / mag, a.y / mag, a.z / mag));
}
