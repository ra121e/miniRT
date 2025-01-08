/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:03:59 by xlok              #+#    #+#             */
/*   Updated: 2025/01/08 10:41:54 by athonda          ###   ########.fr       */
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

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_dlist
{
	void	*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_rt
{
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
	char	*title;
}	t_rt;

void	init(t_rt *p);
int		close_win(void *param);
int		handler_key(int keycode, void *param);

// vector utils

t_vec3	vec3_init(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult(t_vec3 a, double b);
t_vec3	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_mag(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
int		get_vec3_from_str(t_vec3 *vec, char *str);



#endif
