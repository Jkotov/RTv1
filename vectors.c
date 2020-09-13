/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:38:05 by epainter          #+#    #+#             */
/*   Updated: 2020/09/13 14:38:05 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_dot		vector_subtraction(t_dot v1, t_dot v2)
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

float		scalar_mult(t_dot vec1, t_dot vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float		abs_vector(t_dot vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

/*
** try with return 1 / abs_vector(vec);
*/

float		revers_abs_vec(t_dot vec)
{
	return (q_rsqrt(scalar_mult(vec, vec)));
}

t_dot		vector_normalize(t_dot vector)
{
	return (vector_mult_num(vector, revers_abs_vec(vector)));
}
