

#include "../include/rtv1.h"

/*
** if something went wrong try
** scalar_mult(direction_vec, direction_vec)
** instead 1 as A in quadratic_equation
*/

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

t_sphere		*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len)
{
	float		cur_len;
	t_dot		vector_to_center;
	t_sphere	*cur_sphere;
	t_sphere	*res;

	res = NULL;
	cur_sphere = scene.sphere;
	while (cur_sphere)
	{
		vector_to_center = vector_subtraction(start, cur_sphere->center);
		if ((cur_len = distance_to_sphere(direction_vector,\
		vector_to_center, cur_sphere->radius)) != NAN)
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


void		add_sphere(t_sphere **list, t_sphere sphere)
{
	t_sphere *tmp;

	if (!*list)
	{
		*list = (t_sphere *)malloc(sizeof(t_sphere));
		tmp = *list;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_sphere*)malloc(sizeof(t_sphere));
		tmp = tmp->next;
	}
	*tmp = sphere;
}
