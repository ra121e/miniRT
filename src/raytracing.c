/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:08 by athonda           #+#    #+#             */
/*   Updated: 2025/01/20 22:05:39 by athonda          ###   ########.fr       */
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
	p->ray_direction = vec3_normalize(vec3_add(p->c.d_center, \
									vec3_add(vec_x, vec_y)));
	p->ray_start = p->c.position;
}

void	intersection(t_rt *p, int x, int y)
{
	t_intersection	tmp;
	t_ray			ray;
	int				i;

	ray.direction = p->ray_direction;
	ray.start = p->ray_start;
	i = -1;
	while (++i < p->nb_obj)
	{
		assign_obj(p, i);
		if (p->obj[i]->type == SPHERE)
			tmp = quadratic_formula(p, ray);
		else if (p->obj[i]->type == PLANE)
			tmp = liner_equation(p, ray);
		else if (p->obj[i]->type == CYLINDER)
			tmp = cylinder_formula(p, ray);
		if (tmp.yes_intersection && tmp.solution >= 0 \
			&& tmp.solution <= p->nearest[x][y])
		{
			p->nearest_object[x][y] = tmp.type;
			p->nearest[x][y] = tmp.solution;
			p->pi = tmp.position;
			p->ni = tmp.normal;
		}
	}
}

int	raytracing(t_rt *p)
{
	int	x;
	int	y;

	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	if (p->img == NULL)
		return (1);
	p->addr = mlx_get_data_addr(p->img, &p->bpp, &p->line_size, &p->endian);
	if (p->addr == NULL)
		return (1);
	x = -1;
	while (++x < p->win_x)
	{
		y = -1;
		while (++y < p->win_y)
		{
			screen(p, x, y);
			intersection(p, x, y);
			diffuse(p, x, y);
			specular(p, x, y);
			shadow(p, 0);
			draw(p, x, y);
		}
	}
	return (0);
}
