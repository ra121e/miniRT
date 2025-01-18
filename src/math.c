/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:28:22 by athonda           #+#    #+#             */
/*   Updated: 2025/01/18 12:42:36 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_intersection	liner_equation(t_rt *p, t_ray ray)
{
	double			denominator;
	double			numerator;
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
	t_vec3			p1;
	t_vec3			p2;
	double			height_t1;
	double			height_t2;
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
	b = 2 * vec3_dot(vec3_cross(ray.direction, p->cy.normal), \
					 vec3_cross(vec3_sub(ray.start, p->cy.center), p->cy.normal));
	c = vec3_mag(vec3_cross(vec3_sub(ray.start, p->cy.center), p->cy.normal));
	c = c * c - p->cy.radius * p->cy.radius;
	d = b * b - 4 * a * c;
	*t1 = (-b - sqrt(d)) / (2 * a);
	*t2 = (-b + sqrt(d)) / (2 * a);
	return (d);
}

t_intersection	cylinder_formula(t_rt *p, t_ray ray)
{
	double			d;
	double			t1;
	double			t2;
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
	double			a;
	double			b;
	double			c;
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
	tmp.solution = (-b - sqrt(p->discriminant)) / (2 * a);
	tmp.position = vec3_add(ray.start, vec3_mult(ray.direction, tmp.solution));
	tmp.normal = vec3_normalize(vec3_sub(tmp.position, p->sp.center));
	tmp.type = SPHERE;
	return (tmp);
}
