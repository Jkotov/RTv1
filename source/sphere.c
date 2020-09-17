/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:52:17 by epainter          #+#    #+#             */
/*   Updated: 2020/09/17 18:51:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** if something went wrong try
** scalar_mult(direction_vec, direction_vec)
** instead 1 as A in quadratic_equation
*/

float			distance_to_sphere_cached(t_dot direction_vec,\
t_sphere *sphere, t_dot start)
{
	float		solutions[2];

	sphere_cache_calc(sphere, start);
	if (!quadratic_equation((t_dot){1,\
	2 * scalar_mult(direction_vec, sphere->cache->center_start_vec),\
	sphere->cache->c_coeff}, &solutions[0], &solutions[1]))
		return (NAN);
	if (solutions[0] > solutions[1])
		solutions[0] = solutions[1];
	return (solutions[0]);
}

float			distance_to_sphere(t_dot direction_vec,\
t_dot vec_to_center, float radius)
{
	float		solutions[2];

	if (!quadratic_equation((t_dot){1,\
	2 * scalar_mult(direction_vec, vec_to_center),\
	scalar_mult(vec_to_center, vec_to_center) - radius\
	* radius}, &solutions[0], &solutions[1]))
		return (NAN);
	if (solutions[0] > solutions[1])
		solutions[0] = solutions[1];
	return (solutions[0]);
}

void			sphere_cache_calc(t_sphere *sphere, t_dot start)
{
	char	flag;

	flag = 0;
	if (sphere->radius != sphere->cache->radius)
	{
		sphere->cache->radius = sphere->radius;
		sphere->cache->sqr_radius = sphere->radius * sphere->radius;
		flag = 1;
	}
	if (!dot_cmp(sphere->cache->start, start) ||
	!dot_cmp(sphere->center, sphere->cache->center))
	{
		sphere->cache->start = start;
		sphere->cache->center = sphere->center;
		flag = 1;
	}
	if (flag)
	{
		sphere->cache->center_start_vec =
		vector_subtraction(start, sphere->center);
		sphere->cache->c_coeff = scalar_mult(sphere->cache->center_start_vec,\
		sphere->cache->center_start_vec) - sphere->cache->sqr_radius;
	}
}

/*
** Thinks about cache later
*/

t_sphere		*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len)
{
	float		cur_len;
	t_dot		center_start_vec;
	t_sphere	*cur_sphere;
	t_sphere	*res;

	res = NULL;
	cur_sphere = scene.sphere;
	while (cur_sphere)
	{
		center_start_vec = vector_subtraction(start, cur_sphere->center);
		cur_len = distance_to_sphere(direction_vector,\
		center_start_vec, cur_sphere->radius);
		if (cur_len != NAN)
		{
			if (*len > cur_len && cur_len > 0)
			{
				res = cur_sphere;
				*len = cur_len;
			}
		}
		cur_sphere = cur_sphere->next;
	}
	return (res);
}

void			add_sphere(t_sphere **list, t_sphere sphere)
{
	t_sphere *tmp;

	if (!*list)
	{
		if (!(*list = (t_sphere *)malloc(sizeof(t_sphere))))
			sdl_error("Alloc error");
		tmp = *list;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_sphere*)malloc(sizeof(t_sphere))))
			sdl_error("Alloc error");
		tmp = tmp->next;
	}
	if (!(sphere.cache = (t_sphere_cache*)malloc(sizeof(t_sphere_cache))))
		sdl_error("Alloc error");
	sphere.cache->radius = NAN;
	sphere.cache->start = (t_dot){NAN, NAN, NAN};
	sphere.cache->center = (t_dot){NAN, NAN, NAN};
	*tmp = sphere;
}
