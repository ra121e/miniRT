/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:03:59 by xlok              #+#    #+#             */
/*   Updated: 2025/01/18 21:33:38 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define SHINE 100
# define DELTA 1.0 / 512

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
typedef struct s_wrap			t_wrap;
typedef struct s_fcolor			t_fcolor;
typedef struct s_object			t_object;
typedef struct s_a_light		t_a_light;
typedef struct s_camera			t_camera;
typedef struct s_material		t_material;
typedef struct s_light			t_light;

enum e_shape
{
	NONE,
	PLANE,
	SPHERE,
	SQUARE,
	CYLINDER,
	TRIANGLE
};
typedef enum e_shape			t_shape;

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
	bool	yes_intersection;
	double	solution;
	t_vec3	position;
	t_vec3	normal;
	t_shape	type;
};

// wrap
struct s_wrap
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
	t_vec3	p1;
	t_vec3	p2;
	double	height_t1;
	double	height_t2;
};

// color factor
struct s_fcolor
{
	double	red;
	double	green;
	double	blue;
//	int	r;
//	int	g;
//	int	b;
};

// constants(konstant) of material
struct s_material
{
	t_fcolor	kdif;
	t_fcolor	kspe;
	float		shine;
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
//	double		intensity;//shouldn't intensity be double instead of fcolor?
	t_fcolor	intensity;
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
	double		sx;
	double		sy;
	t_vec3		ray_start;
	t_vec3		ray_direction;
	t_vec3		sp2c;
	t_vec3		pl2c;
	t_vec3		cy2c;
	double		discriminant;
	double		solution;
	double		nearest[800][800];
	t_shape		nearest_object[800][800];
	t_vec3		pi;
	t_vec3		ni;
	t_vec3		pi2l;
	t_vec3		shadow_start;
	t_vec3		shadow_direction;
	bool		yes_shadow;
	t_fcolor	r_a;
	t_fcolor	r_d;
	t_fcolor	r_s;
	t_fcolor	r_surface;
	t_fcolor	r_all;
	char		*title;
	t_camera	c;
	t_object	sp;
	t_object	pl;
	t_object	cy;
	t_light		l;
//	t_fcolor	a;
	t_a_light	a;
}	t_rt;

// input validation
int		input_validation(char *arg);
int		validate_acl(char **e);
int		validate_obj(char **e);

// input validation utils
int		validate_rgb(char *str);
int		validate_vec3(char *str, double min, double max);

// init
void	init(t_rt *p, char *rt);
int		init_file(char *rt, t_rt *p);
void	init_acl(char **e, t_rt *p);
void	init_obj(char **e, t_rt *p);

// init utils
int		init_rgb(char *str, t_fcolor *p);
int		init_vec3(char *str, t_vec3 *p);
void	init_nearest(t_rt *p);

// math caluculation
t_intersection	liner_equation(t_rt *p, t_ray ray);
t_intersection	quadratic_formula(t_rt *p, t_ray ray);
t_intersection	cylinder_formula(t_rt *p, t_ray ray);

// general
void	cleanup(t_rt *p, int status);
int		close_win(void *param);
int		handler_key(int keycode, void *param);
void	screen(t_rt *p, double x, double y);
void	diffuse(t_rt *p, int x, int y);
void	specular(t_rt *p, int x, int y);
void	shadow(t_rt *p, int i);
int		color(t_rt *p);
void	draw(t_rt *p, int x, int y);
int		raytracing(t_rt *p);
int		raytracing_pl(t_rt *p);
int		raytracing_cy(t_rt *p);
int		move_camera(t_rt *p, t_vec3 offset);

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

// fcolor utils
t_fcolor	fcolor_normalize(t_fcolor fcolor);
t_fcolor	fcolor_init(double red, double green, double blue);
t_fcolor	fcolor_add(t_fcolor a, t_fcolor b);
t_fcolor	fcolor_mult(t_fcolor a, t_fcolor b);
t_fcolor	fcolor_mult_scalar(t_fcolor a, double b);
t_fcolor	fcolor_rgb_convert(double r, double g, double b);

// dlist
t_dlist	*dlst_new(void *content);
t_dlist	*dlst_add_right(t_dlist **lst, t_dlist *new);

// math utils
double	deg2rad(double a);

#endif
