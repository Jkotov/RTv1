/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:50:01 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 07:17:24 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		light_balancer(t_scene *scene)
{
	t_light	*tmp;
	float	max_light;

	max_light = 0;
	tmp = scene->light;
	while (tmp)
	{
		max_light += tmp->base_intensity;
		tmp = tmp->next;
	}
	tmp = scene->light;
	while (tmp)
	{
		tmp->intensity = tmp->base_intensity / max_light;
		tmp = tmp->next;
	}
}

void		add_light(t_scene *scene, t_dot center, float intensity)
{
	t_light *tmp;

	if (intensity > 0)
	{
		tmp = scene->light;
		if (!tmp)
		{
			tmp = (t_light *)malloc(sizeof(t_light));
			scene->light = tmp;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = (t_light*)malloc(sizeof(t_light));
			tmp = tmp->next;
		}
		tmp->center = center;
		tmp->base_intensity = intensity;
		tmp->next = NULL;
		light_balancer(scene);
	}
}

float		specular(t_compute_light_p p,\
t_dot light_vector, float intensity)
{
	t_dot	specular_vector;
	float	tmp;

	if (p.specular <= 0)
		return (0);
	specular_vector =\
	vector_sub(vector_mult_num(vector_mult_num(p.normal_vec,\
	2), scalar_mult(p.normal_vec, light_vector)), light_vector);
	if (scalar_mult(specular_vector, p.direction_vec) < 0)
		return (0);
	tmp = powf(scalar_mult(specular_vector, p.direction_vec)\
	* revers_abs_vec(specular_vector), p.specular) * intensity;
	return (tmp);
}

char		sphere_on_light(t_dot start, t_dot direction_vector,\
t_scene scene)
{
	float		cur_len;
	t_surface	*cur_shape;

	cur_shape = scene.shape;
	while (cur_shape)
	{
		cur_len = distance_to_shape(cur_shape->c, direction_vector, start);
		if (!isnan(cur_len) && cur_len > 0 && cur_len < 1)
		{
			return (0);
		}
		cur_shape = cur_shape->next;
	}
	return (1);
}

float		lighting(t_scene scene, t_compute_light_p p)
{
	float	res;
	t_light	*cur_light;
	t_dot	light_vector;
	float	tmp;

	res = scene.light->intensity;
	cur_light = scene.light->next;
	while (cur_light)
	{
		light_vector = vector_sub(cur_light->center, p.dot);
		tmp = INFINITY;
		if (sphere_on_light(p.dot, ((light_vector)),\
		scene))
		{
			light_vector = vector_normalize(light_vector);
			tmp = scalar_mult(p.normal_vec, light_vector)\
			* cur_light->intensity;
			res = tmp > 0 ? res + tmp : res;
			res += specular(p, light_vector, cur_light->intensity);
		}
		cur_light = cur_light->next;
	}
	res = res > 1 ? 1 : res;
	return (res);
}
