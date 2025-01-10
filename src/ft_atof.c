/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:19:45 by athonda           #+#    #+#             */
/*   Updated: 2025/01/10 18:20:41 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (1);
	return (0);
}

int	ft_space_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

double	ft_atof(char *str)
{
	double	nb;
	double	nb_dec;
	int		dp;
	int		i;
	int		sign;

	sign = 1;
	i = ft_space_sign(str, &sign);
	nb = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	dp = 0;
	nb_dec = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nb_dec = nb_dec * 10 + (str[i++] - '0');
		dp++;
	}
	nb = nb + nb_dec / pow(10, dp);
	return (nb * sign);
}
