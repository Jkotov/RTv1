/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:30:13 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 18:33:56 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		scalar_mult(t_dot vec1, t_dot vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float		abs_vector(t_dot vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

float		revers_abs_vec(t_dot vec)
{
	return (1 / abs_vector(vec));
}

t_dot		vector_normalize(t_dot vector)
{
	return (vector_mult_num(vector, revers_abs_vec(vector)));
}
