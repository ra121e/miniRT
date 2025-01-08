/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:48 by xlok              #+#    #+#             */
/*   Updated: 2025/01/08 21:50:30 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	input_validation(char *arg)
{
	if (ft_strlen(arg) < 4
		|| ft_strncmp(arg + ft_strlen(arg) - 3, ".rt", 4)
		|| !ft_isalnum(*arg))
		return (ft_dprintf(2, "Error: "
				"Pls enter a .rt file starting with alphanumeric\n"), 1);
	return (0);
}
