/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:03:59 by xlok              #+#    #+#             */
/*   Updated: 2025/01/12 16:06:38 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
# include "mlx_int.h"

typedef struct s_vec3			t_vec3;
typedef struct s_dlist			t_dlist;
typedef struct s_ray			t_ray;
typedef struct s_intersection	t_intersection;
typedef struct s_fcolor			t_fcolor;
typedef struct s_object			t_object;
typedef struct s_camera			t_camera;
typedef struct s_material		t_material;
typedef struct s_light			t_light;

// math
// vector
struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

// ray (line in math)
struct s_ray
{
	t_vec3	start;
	t_vec3	direction;
};

// intersection
struct s_intersection
{
	bool	has_intersection;
	double	distance;
	t_vec3	position;
	t_vec3	normal;
};

// color factor
struct s_fcolor
{
	double	red;
	double	green;
	double	blue;
};

// constants(konstant) of material
struct s_material
{
	t_fcolor	kdif;
	t_fcolor	kspe;
	float		shine;
};

enum	e_shape
{
	PLANE,
	SPHERE,
	SQUARE,
	CYLINDER,
	TRIANGLE
};

struct s_object
{
	enum e_shape	type;
	t_vec3			center;
	t_vec3			normal;
	double			radius;
	double			side_size;
	double			height;
	t_material		material;
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			p3;
};

struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
	double	distance;
	t_vec3	x_basis;
	t_vec3	y_basis;
	t_vec3	d_center;
	t_img	img;
};

// light source
struct s_light
{
	t_vec3		position;
	t_fcolor	intensity;
};

// data structure

struct s_dlist
{
	void	*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
};

typedef struct s_rt
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_size;
	int			endian;
	int			win_x;
	int			win_y;
	double		sx;
	double		sy;
	t_vec3		ray_start;
	t_vec3		ray_direction;
	t_vec3		sp2c;
	t_vec3		cy2c;
	double		discriminant;
	double		solution;
	t_vec3		pi;
	t_vec3		ni;
	char		*title;
	t_camera	c;
	t_object	sp;
	t_object	pl;
	t_object	cy;
	t_light		l;
	t_fcolor	a;
//	t_dlist		*camera;
//	t_list		*object;
//	t_list		*light;
}	t_rt;

int		init(t_rt *p);
int		close_win(void *param);
int		handler_key(int keycode, void *param);

// vector utils

t_vec3	vec3_init(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult(t_vec3 a, double b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_mag(t_vec3 a);
t_vec3	vec3_normalize(t_vec3 a);
int		get_vec3_from_str(t_vec3 *vec, char *str);

// dlist

t_dlist	*dlst_new(void *content);
t_dlist	*dlst_add_right(t_dlist **lst, t_dlist *new);


int	raytracing(t_rt *p);

// math utils

double	deg2rad(double a);

#endif
