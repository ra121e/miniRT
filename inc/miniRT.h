/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:03:59 by xlok              #+#    #+#             */
/*   Updated: 2025/01/04 19:10:14 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H 
# define MINIRT_H 

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

typedef struct s_rt
{
	void	*mlx;
	void	*win;
}	t_rt;

#endif
