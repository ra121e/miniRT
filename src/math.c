/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:28:22 by athonda           #+#    #+#             */
/*   Updated: 2025/01/18 17:05:58 by athonda          ###   ########.fr       */
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

t_intersection	cylinder_intersection(t_rt *p, t_wrap *w, t_ray ray)
{
	t_intersection	tmp;

	w->p1 = vec3_add(ray.start, vec3_mult(ray.direction, w->t1));
	w->p2 = vec3_add(ray.start, vec3_mult(ray.direction, w->t2));
	w->height_t1 = vec3_dot(vec3_sub(w->p1, p->cy.center), p->cy.normal);
	w->height_t2 = vec3_dot(vec3_sub(w->p2, p->cy.center), p->cy.normal);
	if (w->t1 >= 0 && w->height_t1 >= 0 && (w->height_t1 <= p->cy.height))
	{
		tmp.yes_intersection = true;
		tmp.solution = w->t1;
		tmp.position = w->p1;
		tmp.normal = vec3_normalize(vec3_sub(vec3_sub(w->p1, p->cy.center), \
									vec3_mult(p->cy.normal, w->height_t1)));
	}
	else if (w->height_t2 >= 0 && (w->height_t2 <= p->cy.height))
	{
		tmp.yes_intersection = true;
		tmp.solution = w->t2;
		tmp.position = w->p2;
		tmp.normal = vec3_normalize(vec3_sub(vec3_mult(p->cy.normal, \
					w->height_t2), vec3_sub(w->p2, p->cy.center)));
	}
	else
		tmp.yes_intersection = false;
	return (tmp);
}

void	find_solution(t_rt *p, t_wrap *w, t_ray ray)
{
	p->cy2c = vec3_sub(ray.start, p->cy.center);
	w->a = vec3_mag(vec3_cross(ray.direction, p->cy.normal));
	w->a = w->a * w->a;
	w->b = 2 * vec3_dot(vec3_cross(ray.direction, p->cy.normal), \
						vec3_cross(vec3_sub(ray.start, p->cy.center), \
											p->cy.normal));
	w->c = vec3_mag(vec3_cross(vec3_sub(ray.start, p->cy.center), \
										p->cy.normal));
	w->c = w->c * w->c - p->cy.radius * p->cy.radius;
	w->d = w->b * w->b - 4 * w->a * w->c;
	w->t1 = (-w->b - sqrt(w->d)) / (2 * w->a);
	w->t2 = (-w->b + sqrt(w->d)) / (2 * w->a);
}

t_intersection	cylinder_formula(t_rt *p, t_ray ray)
{
	t_intersection	tmp;
	t_wrap			w;

	w.d = 0;
	find_solution(p, &w, ray);
	if (w.d < 0)
	{
		tmp.yes_intersection = false;
		return (tmp);
	}
	tmp = cylinder_intersection(p, &w, ray);
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
	if (((-b - sqrt(p->discriminant)) / (2 * a)) < 0)
		tmp.solution = (-b + sqrt(p->discriminant)) / (2 * a);
	else
		tmp.solution = (-b - sqrt(p->discriminant)) / (2 * a);
	tmp.position = vec3_add(ray.start, vec3_mult(ray.direction, tmp.solution));
	tmp.normal = vec3_normalize(vec3_sub(tmp.position, p->sp.center));
	tmp.type = SPHERE;
	return (tmp);
}
