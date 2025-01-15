/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/15 20:28:31 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	screen(t_rt *p, double x, double y)
{
	double	converted_x;
	double	converted_y;
	t_vec3	vec_x;
	t_vec3	vec_y;

	converted_x = x - p->win_x / 2;
	converted_y = -y + p->win_y / 2;
	vec_x = vec3_mult(p->c.x_basis, converted_x);
	vec_y = vec3_mult(p->c.y_basis, converted_y);
	p->ray_direction = vec3_normalize(vec3_add(p->c.d_center, vec3_add(vec_x, vec_y)));
	p->ray_start = p->c.position;
}

t_intersection	liner_equation(t_rt *p, t_ray ray)
{
	double	denominator;
	double	numerator;
	t_intersection	tmp;

	p->pl2c = vec3_sub(ray.start, p->pl.center);
	denominator = vec3_dot(vec3_mult(ray.direction, -1), p->pl.normal);
	numerator = vec3_dot(p->pl2c, p->pl.normal);
	if (denominator == 0)
	{
		tmp.yes_intersection = false;
		return (tmp);
	}
	tmp.yes_intersection = true;
	tmp.solution = numerator / denominator;
	tmp.position = vec3_add(ray.start, vec3_mult(ray.direction, tmp.solution));
	if (denominator > 0)
		tmp.normal = p->pl.normal;
	else
		tmp.normal = vec3_mult(p->pl.normal, -1);
	tmp.type = PLANE;
	return (tmp);
}

t_intersection	cylinder_intersection(t_rt *p, double t1, double t2, t_ray ray)
{
	t_vec3	p1;
	t_vec3	p2;
	double	height_t1;
	double	height_t2;
	t_intersection	tmp;

	p1 = vec3_add(ray.start, vec3_mult(ray.direction, t1));
	p2 = vec3_add(ray.start, vec3_mult(ray.direction, t2));
	height_t1 = vec3_dot(vec3_sub(p1, p->cy.center), p->cy.normal);
	height_t2 = vec3_dot(vec3_sub(p2, p->cy.center), p->cy.normal);
	if (height_t1 >= 0 && (height_t1 <= p->cy.height))
	{
		tmp.yes_intersection = true;
		tmp.solution = t1;
		tmp.position = p1;
		tmp.normal = vec3_normalize(vec3_sub(vec3_sub(p1, p->cy.center), vec3_mult(p->cy.normal, height_t1)));
	}
	else if (height_t2 >= 0 && (height_t2 <= p->cy.height))
	{
		tmp.yes_intersection = true;
		tmp.solution = t2;
		tmp.position = p2;
		tmp.normal = vec3_normalize(vec3_sub(vec3_mult(p->cy.normal, height_t2), vec3_sub(p2, p->cy.center)));
	}
	else
		tmp.yes_intersection = false;
	return (tmp);
}

double	find_solution(t_rt *p, double *t1, double *t2, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	d;

	p->cy2c = vec3_sub(ray.start, p->cy.center);
	a = vec3_mag(vec3_cross(ray.direction, p->cy.normal));
	a = a * a;
	b = 2 * vec3_dot(vec3_cross(ray.direction, p->cy.normal), vec3_cross(vec3_sub(ray.start, p->cy.center), p->cy.normal));
	c = vec3_mag(vec3_cross(vec3_sub(ray.start, p->cy.center), p->cy.normal));
	c = c * c - p->cy.radius * p->cy.radius;
	d = b * b - 4 * a * c;
	*t1 = (-b - sqrt(d)) / ( 2 * a);
	*t2 = (-b + sqrt(d)) / ( 2 * a);
	return (d);
}

t_intersection	cylinder_formula(t_rt *p, t_ray ray)
{
	double	d;
	double	t1;
	double	t2;
	t_intersection	tmp;

	d = find_solution(p, &t1, &t2, ray);
	if (d < 0)
	{
		tmp.yes_intersection = false;
		return (tmp);
	}
	tmp = cylinder_intersection(p, t1, t2, ray);
	tmp.type = CYLINDER;
	return (tmp);
}

t_intersection	quadratic_formula(t_rt *p, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	t_intersection	tmp;

	p->sp2c = vec3_sub(ray.start, p->sp.center);
	a = vec3_mag(ray.direction) * vec3_mag(ray.direction);
	b = 2 * vec3_dot(p->sp2c, ray.direction);
	c = vec3_dot(p->sp2c, p->sp2c) - p->sp.radius * p->sp.radius;
	p->discriminant = b * b - 4 * a * c;
	if (p->discriminant < 0)
	{
		tmp.yes_intersection = false;
		return (tmp);
	}
	tmp.yes_intersection = true;
	tmp.solution = (-b -sqrt(p->discriminant)) / (2 * a);
	tmp.position = vec3_add(ray.start, vec3_mult(ray.direction, tmp.solution));
	tmp.normal = vec3_normalize(vec3_sub(tmp.position, p->sp.center));
	tmp.type = SPHERE;
	return (tmp);
}

void	intersection(t_rt *p, int x, int y, t_ray ray)
{
	t_intersection	tmp;
	int	i;

	i = 0;
	while (++i < 4)
	{
		if (i == 1)
			tmp = quadratic_formula(p, ray);
		else if (i == 2)
			tmp = liner_equation(p, ray);
		else if (i == 3)
			tmp = cylinder_formula(p, ray);
		if (tmp.yes_intersection && tmp.solution >= 0 && tmp.solution <= p->nearest[x][y])
		{
			p->nearest_object[x][y] = tmp.type;
			p->nearest[x][y] = tmp.solution;
			p->pi = tmp.position;
			p->ni = tmp.normal;
		}
	}
}

void	diffuse(t_rt *p, int x, int y)
{
	t_vec3		l;
	double		dotproduct;
	t_fcolor	kdif;

	if (p->nearest_object[x][y] == PLANE)
		kdif = p->pl.material.kdif;
	else if (p->nearest_object[x][y] == SPHERE)
		kdif = p->sp.material.kdif;
	else if (p->nearest_object[x][y] == CYLINDER)
		kdif = p->cy.material.kdif;
	else
		return ;
	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(kdif, p->l.intensity), dotproduct);
}

void	specular(t_rt *p, int x, int y)
{
	t_vec3		l;
	t_vec3		v;
	t_vec3		r;
	t_fcolor	kspe;

	if (p->nearest_object[x][y] == PLANE)
		kspe = p->pl.material.kspe;
	else if (p->nearest_object[x][y] == SPHERE)
		kspe = p->sp.material.kspe;
	else if (p->nearest_object[x][y] == CYLINDER)
		kspe = p->cy.material.kspe;
	else
		return ;
	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(kspe, p->l.intensity), pow(vec3_dot(v, r), SHINE));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

void	shadow(t_rt *p)
{
	double	light_distance;
	t_intersection	tmp;
	t_ray	ray;
	int	i;

	p->pi2l = vec3_sub(p->l.position, p->pi);
	p->shadow_start = vec3_add(p->pi, vec3_mult(vec3_normalize(p->pi2l), DELTA));
	p->shadow_direction = vec3_normalize(p->pi2l);
	light_distance = vec3_mag(p->pi2l) - DELTA;
	ray.direction = p->shadow_direction;
	ray.start = p->shadow_start;
	i = 0;
	while (++i < 4)
	{
		if (i == 1)
			tmp = quadratic_formula(p, ray);
		else if (i == 2)
			tmp = cylinder_formula(p, ray);
		else if (i == 3)
			tmp = liner_equation(p, ray);
		if (tmp.yes_intersection == true && tmp.solution >= 0 && tmp.solution <= light_distance)
			p->r_d = fcolor_init(0, 0, 0);
	}
}

int	color(t_rt *p)
{
	int			red;
	int			green;
	int			blue;
	int			rgb;

	p->r_all = fcolor_add(fcolor_add(p->r_a, p->r_d), p->r_s);
	red = (int)(255 * p->r_all.red);
	green = (int)(255 * p->r_all.green);
	blue = (int)(255 * p->r_all.blue);
	rgb = (red << 16) + (green << 8) + (blue);
	return (rgb);
}

void	draw(t_rt *p, int x, int y)
{
	int	offset;

	if (p->nearest_object[x][y])
	{
		offset = y * p->line_size + (x * p->bpp / 8);
		*(int *)(p->addr + offset) = color(p);
	}
	else
	{
		offset = y * p->line_size + (x * p->bpp / 8);
		*(int *)(p->addr + offset) = (128 << 24) | 0x00FFFFFF;
	}
}

int	raytracing(t_rt *p)
{
	int	x;
	int	y;
	t_ray	ray;

	x = -1;
	while (++x < p->win_x)
	{
		y = -1;
		while (++y < p->win_y)
		{
			screen(p, x, y);
			ray.direction = p->ray_direction;
			ray.start = p->ray_start;
			intersection(p, x, y, ray);
			diffuse(p, x, y);
			specular(p, x, y);
			shadow(p);
			draw(p, x, y);
		}
	}
	return (0);
}