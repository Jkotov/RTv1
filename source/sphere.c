/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:52:17 by epainter          #+#    #+#             */
/*   Updated: 2020/09/28 19:03:39 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			distance_to_conic(t_surface_coeffs s, t_dot v, t_dot start)
{
	float		solutions[2];
	float		a;
	float		b;
	float		c;

	a = s.a * v.x * v.x + s.b * v.y * v.y + s.c * v.z * v.z + s.f2 * v.y *\
	v.z + s.g2 * v.x * v.z + s.h2 * v.x * v.y;
	b = 2 * s.a * start.x * v.x + 2 * s.b * start.y * v.y + 2 * s.c *\
	start.z * v.z + s.f2 * v.y * start.z + s.f2 * v.z * start.y + s.g2 *\
	v.x * start.z + s.g2 * v.z * start.x + s.h2 * v.y * start.x + s.h2 *\
	v.x * start.y + s.p2 * v.x + s.q2 * v.y + s.r2 * v.z;
	c = s.a * start.x * start.x + s.b * start.y * start.y + s.c * start.z *\
	start.z + s.f2 * start.y * start.z + s.g2 * start.x * start.z + s.h2 *\
	start.x * start.y + s.p2 * start.x + s.q2 * start.y + s.r2 * start.z + s.d;
	if (!a && b)
		return (-c / b);
	if (!quadratic_equation((t_dot){a, b, c}, &solutions[0], &solutions[1]))
		return (NAN);
	if (solutions[0] < 0)
		solutions[0] = solutions[1];
	if (solutions[0] > solutions[1] && solutions[1] > 0)
		solutions[0] = solutions[1];
	return (solutions[0]);
}

t_surface		*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len)
{
	float		cur_len;
	t_surface	*cur_conic;
	t_surface	*res;

	res = NULL;
	cur_conic = scene.conic;
	while (cur_conic)
	{
		cur_len = distance_to_conic(cur_conic->c, direction_vector, start);
		if (!isnan(cur_len) )
		{
			if (*len > cur_len && cur_len > 0)
			{
				res = cur_conic;
				*len = cur_len;
			}
		}
		cur_conic = cur_conic->next;
	}
	return (res);
}

void			add_sphere(t_surface **list, t_surface surface)
{
	t_surface	*tmp;
	t_dot		nil;

	nil = (t_dot){0, 0, 0};
	if (!*list)
	{
		if (!(*list = (t_surface *)malloc(sizeof(t_surface))))
			sdl_error("Alloc error");
		tmp = *list;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_surface*)malloc(sizeof(t_surface))))
			sdl_error("Alloc error");
		tmp = tmp->next;
	}
	surface.cache = (t_surface_cache){surface.c, nil, nil};
	surface.c = surface_shift(&surface);
	surface.c = rotate_surface(&surface);
	*tmp = surface;
}
