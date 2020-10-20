/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:38:05 by epainter          #+#    #+#             */
/*   Updated: 2020/09/30 16:21:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_dot		vector_reflection(t_dot direction_vec, t_dot normal_vec)
{
	t_dot	reflected_vec;

	reflected_vec =\
	vector_sub(direction_vec,\
	vector_mult_num(vector_mult_num(normal_vec,\
	2), scalar_mult(normal_vec, direction_vec)));
	reflected_vec = vector_normalize(reflected_vec);
	return (reflected_vec);
}

t_dot		vector_sub(t_dot v1, t_dot v2)
{
	return ((t_dot){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_dot		vector_sum(t_dot v1, t_dot v2)
{
	return ((t_dot){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_dot		vector_mult_num(t_dot v, float num)
{
	return ((t_dot){v.x * num, v.y * num, v.z * num});
}
