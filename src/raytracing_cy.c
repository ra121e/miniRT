/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/14 00:46:52 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	cylinder_formula(t_rt *p)
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
//	p->solution = (-b -sqrt(p->discriminant)) / (2 * a);
//	p->pi = vec3_add(p->ray_start, vec3_mult(p->ray_direction, p->solution));
//	p->ni = vec3_normalize(vec3_sub(p->pi, p->sp.center));
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

int	raytracing_cy(t_rt *p)
{
	int	x;
	int	y;
	int	offset;

	x = -1;
	while (++x < p->win_x)
	{
		y = -1;
		while (++y < p->win_y)
		{
			screen(p, x, y);
			cylinder_formula(p);
			if (p->discriminant >= 0)
			{
				if (p->solution < 0 || \
					(p->nearest[x][y] > 0 && p->solution > 0 && \
					p->nearest[x][y] < p->solution))
					continue ;
				p->nearest[x][y] = p->solution;
				diffuse_cy(p);
				specular_cy(p);
				offset = y * p->line_size + (x * p->bpp / 8);
				*(int *)(p->addr + offset) = color(p);
			}
			else
			{
//				offset = y * p->line_size + (x * p->bpp / 8);
//				*(int *)(p->addr + offset) = (128 << 24) | 0x00FFFFFF;
			}
		}
	}
	return (0);
}