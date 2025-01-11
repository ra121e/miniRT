/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:03:59 by xlok              #+#    #+#             */
/*   Updated: 2025/01/11 18:18:04 by xlok             ###   ########.fr       */
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
# include "mlx_int.h"

// x,y,z coordinates limits in input validation

# define XYZ_MIN -400
# define XYZ_MAX 400

typedef struct s_vec3			t_vec3;
typedef struct s_dlist			t_dlist;
typedef struct s_ray			t_ray;
typedef struct s_intersection	t_intersection;
typedef struct s_fcolor			t_fcolor;
typedef struct s_object			t_object;
typedef struct s_a_light		t_a_light;
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
// rgb int not double
struct s_fcolor
{
	int	r;
	int	g;
	int	b;
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
	double			diameter;
	double			height;
	t_material		material;
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			p3;
};

// Ambient lighting
struct s_a_light
{
	double		intensity;
	t_fcolor	color;
};

struct s_camera
{
	t_vec3	pos;
	t_vec3	orientation;
	double	fov;
	t_vec3	x_basis;
	t_vec3	y_basis;
	t_vec3	d_venter;
	t_img	img;
};

// light source
struct s_light
{
	t_vec3		position;
	double		intensity;//intensity should be double not rgb
	t_fcolor	color;
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
	char		*title;
	t_camera	c;
	t_object	sp;
	t_object	pl;
	t_object	cy;
	t_light		l;
	t_a_light	a;
//	t_dlist		*camera;
//	t_list		*object;
//	t_list		*light;
}	t_rt;

// input validation

int		input_validation(char *arg);
int		validate_acl(char **e);
int		validate_obj(char **e);

// input validation utils

int		validate_rgb(char *str);
int		validate_vec3(char *str, double min, double max);

// init

int		init(t_rt *p, char *rt);
int		init_file(char *rt, t_rt *p);
int		init_acl(char **e, t_rt *p);
int		init_obj(char **e, t_rt *p);

// init utils

int		init_rgb(char *str, t_fcolor *p);
int		init_vec3(char *str, t_vec3 *p);

// general

int		close_win(void *param);
int		handler_key(int keycode, void *param);

// general utils

int		is_int(char *str);
int		is_double(char *str);
double	ft_atof(char *str);

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

#endif
