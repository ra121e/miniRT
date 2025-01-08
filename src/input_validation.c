/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/08 21:01:50 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	input_validation(char *arg)
{
	int	i;

	if (ft_strlen(arg) < 4 || ft_strncmp(arg + ft_strlen(arg) - 3, ".rt", 4)
		|| !ft_isalnum(*arg))
		return (ft_dprintf(
				2, "Pls enter a .rt file starting with alphanumeric\n"), 1);
	i = -1;
	while (arg[++i])
	{
	}
	return (0);
}
