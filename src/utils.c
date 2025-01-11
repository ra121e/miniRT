/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 07:26:00 by xlok              #+#    #+#             */
/*   Updated: 2025/01/11 19:25:43 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  deg2rad(double a)
{
	return (a / 180 * M_PI);
}

int	is_int(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	is_double(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str != '.')
		if (!ft_isdigit(*str++))
			return (0);
	if (*str == '.')
		str++;
	else
		return (1);
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}
