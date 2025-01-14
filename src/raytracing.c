/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/14 17:28:14 by athonda          ###   ########.fr       */
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

void	liner_equation(t_rt *p, int x, int y)
{
	double	denominator;
	double	numerator;

	p->pl2c = vec3_sub(p->c.position, p->pl.center);
	denominator = vec3_dot(vec3_mult(p->ray_direction, -1), p->pl.normal);
	numerator = vec3_dot(p->pl2c, p->pl.normal);
	p->solution = numerator / denominator;
	if (p->solution >= 0 && \
		(p->nearest[x][y] > 0 && p->solution < p->nearest[x][y]))
	{
		p->nearest[x][y] = p->solution;
		p->nearest_object[x][y] = PLANE;
		p->pi = vec3_add(p->ray_start, vec3_mult(p->ray_direction, p->solution));
		if (denominator > 0)
			p->ni = p->pl.normal;
		else
			p->ni = vec3_mult(p->pl.normal, -1);
	}
}

void	cylinder_intersection(t_rt *p, double t1, double t2)
{
	t_vec3	p1;
	t_vec3	p2;
	double	height_t1;
	double	height_t2;

	p1 = vec3_add(p->ray_start, vec3_mult(p->ray_direction, t1));
	p2 = vec3_add(p->ray_start, vec3_mult(p->ray_direction, t2));
	height_t1 = vec3_dot(vec3_sub(p1, p->cy.center), p->cy.normal);
	height_t2 = vec3_dot(vec3_sub(p2, p->cy.center), p->cy.normal);
	if (height_t1 >= 0 && (height_t1 <= p->cy.height))
	{
		p->solution = t1;
		p->pi = p1;
		p->ni = vec3_normalize(vec3_sub(vec3_sub(p1, p->cy.center), vec3_mult(p->cy.normal, height_t1)));
	}
	else if (height_t2 >= 0 && (height_t2 <= p->cy.height))
	{
		p->solution = t2;
		p->pi = p2;
		p->ni = vec3_normalize(vec3_sub(vec3_mult(p->cy.normal, height_t2), vec3_sub(p2, p->cy.center)));
	}
	else
	{
		p->solution = -1;
	}
}

void	cylinder_formula(t_rt *p, int x, int y)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;

	p->cy2c = vec3_sub(p->c.position, p->cy.center);
	a = vec3_mag(vec3_cross(p->ray_direction, p->cy.normal));
	a = a * a;
	b = 2 * vec3_dot(vec3_cross(p->ray_direction, p->cy.normal), vec3_cross(vec3_sub(p->ray_start, p->cy.center), p->cy.normal));
	c = vec3_mag(vec3_cross(vec3_sub(p->ray_start, p->cy.center), p->cy.normal));
	c = c * c - p->cy.radius * p->cy.radius;
	p->discriminant = b * b - 4 * a * c;
	t1 = (-b - sqrt(p->discriminant)) / ( 2 * a);
	t2 = (-b + sqrt(p->discriminant)) / ( 2 * a);
	cylinder_intersection(p, t1, t2);
	if (p->discriminant >= 0 && \
		(p->nearest[x][y] > 0 && p->solution > 0 && \
		p->solution < p->nearest[x][y]))
	{
		p->nearest[x][y] = p->solution;
		p->nearest_object[x][y] = CYLINDER;
	}
}

void	quadratic_formula(t_rt *p, int x, int y)
{
	double	a;
	double	b;
	double	c;

	p->sp2c = vec3_sub(p->c.position, p->sp.center);
	a = vec3_mag(p->ray_direction) * vec3_mag(p->ray_direction);
	b = 2 * vec3_dot(p->sp2c, p->ray_direction);
	c = vec3_dot(p->sp2c, p->sp2c) - p->sp.radius * p->sp.radius;
	p->discriminant = b * b - 4 * a * c;
	p->solution = (-b -sqrt(p->discriminant)) / (2 * a);
//	if (p->discriminant >= 0 &&
//		(p->solution >= 0 && p->solution < p->nearest[x][y]))
	if (p->discriminant >= 0 && \
		(p->nearest[x][y] > 0 && p->solution > 0 && \
		p->solution < p->nearest[x][y]))
	{
		p->nearest[x][y] = p->solution;
		p->nearest_object[x][y] = SPHERE;
		p->pi = vec3_add(p->ray_start, vec3_mult(p->ray_direction, p->solution));
		p->ni = vec3_normalize(vec3_sub(p->pi, p->sp.center));
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

void	diffuse_cy(t_rt *p)
{
	t_vec3	l;
	double	dotproduct;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(p->cy.material.kdif, p->l.intensity), dotproduct);
}

void	specular_cy(t_rt *p)
{
	t_vec3	l;
	t_vec3	v;
	t_vec3	r;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(p->cy.material.kspe, p->l.intensity), pow(vec3_dot(v, r), p->cy.material.shine));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

void	diffuse_pl(t_rt *p)
{
	t_vec3	l;
	double	dotproduct;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	dotproduct = vec3_dot(p->ni, l);
	if (dotproduct < 0)
		dotproduct = 0;
	p->r_d = fcolor_mult_scalar(fcolor_mult(p->pl.material.kdif, p->l.intensity), dotproduct);
}

void	specular_pl(t_rt *p)
{
	t_vec3	l;
	t_vec3	v;
	t_vec3	r;

	l = vec3_normalize(vec3_sub(p->l.position, p->pi));
	v = vec3_mult(p->ray_direction, -1);
	r = vec3_sub(vec3_mult(vec3_mult(p->ni, vec3_dot(p->ni, l)), 2), l);
	p->r_s = fcolor_mult_scalar(fcolor_mult(p->pl.material.kspe, p->l.intensity), pow(vec3_dot(v, r), p->pl.material.shine));
	if (vec3_dot(v, r) < 0)
		p->r_s = fcolor_init(0, 0, 0);
}

int	color(t_rt *p)
{
	t_fcolor	r_all;
	int			red;
	int			green;
	int			blue;
	int			rgb;

	r_all = fcolor_add(fcolor_add(p->r_a, p->r_d), p->r_s);
	red = (int)(255 * r_all.red);
	green = (int)(255 * r_all.green);
	blue = (int)(255 * r_all.blue);
	rgb = (red << 16) + (green << 8) + (blue);
	return (rgb);
}

int	raytracing(t_rt *p)
{
	int	x;
	int	y;
	int	offset;

	x = 0;
	while (x < p->win_x)
	{
		y = 0;
		while (y < p->win_y)
		{
			screen(p, x, y);
			liner_equation(p, x, y);
			cylinder_formula(p, x, y);
			quadratic_formula(p, x, y);
//			if (p->discriminant >= 0)
//			{
//				if (p->solution < 0 ||
//					(p->nearest[x][y] > 0 && p->solution > 0 &&
//					p->nearest[x][y] < p->solution))
//					continue ;
//				p->nearest[x][y] = p->solution;
//			if (p->nearest_object[x][y] == PLANE)
//			{
			diffuse(p, x, y);
			specular(p, x, y);
			if (p->nearest_object[x][y])
			{
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = color(p);
			}
//			else if (p->nearest_object[x][y] == SPHERE)
//			{
//				diffuse(p);
//				specular(p);
//				offset = y * p->line_size + (x * p->bpp / 8);
//				*(int *)(p->addr + offset) = color(p);
//			}
//			else if (p->nearest_object[x][y] == CYLINDER)
//			{
//				diffuse_cy(p);
//				specular_cy(p);
//				offset = y * p->line_size + (x * p->bpp / 8);
//				*(int *)(p->addr + offset) = color(p);
//			}
//			}
			else
			{
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = (128 << 24) | 0x00FFFFFF;
			}
			y++;
		}
		x++;
	}
	return (0);
}