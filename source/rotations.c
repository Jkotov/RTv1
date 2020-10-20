/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:31:56 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 18:33:56 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix33			fill_rot_m(t_dot angle)
{
	t_matrix33	m;
	float		x;
	float		y;
	float		z;

	x = angle.x;
	y = angle.y;
	z = angle.z;
	m.m[0][0] = (cos(y + z) + cos(y - z)) / 2;
	m.m[0][1] = (-cos(x + y + z) + cos(x - y + z) - cos(x + y - z) +\
	cos(x - y - z) - 2 * sin(x + z) + 2 * sin(x - z)) / 4;
	m.m[0][2] = (-2 * cos(x + z) + 2 * cos(x - z) + sin(x + y + z) -\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m.m[1][0] = (sin(y + z) - sin(y - z)) / 2;
	m.m[1][1] = (2 * cos(x + z) + 2 * cos(x - z) - sin(x + y + z) +\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m.m[1][2] = (-cos(x + y + z) + cos(x - y + z) + cos(x + y - z) -\
	cos(x - y - z) - 2 * sin(x + z) - 2 * sin(x - z)) / 4;
	m.m[2][0] = -sin(y);
	m.m[2][1] = (sin(x + y) + sin(x - y)) / 2;
	m.m[2][2] = (cos(x + y) + cos(x - y)) / 2;
	return (m);
}

t_dot				rotate_vector(t_dot v, t_dot angle)
{
	t_matrix33	m;
	t_dot		res;

	m = fill_rot_m(angle);
	res = (t_dot){v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2],\
	v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2],\
	v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2]};
	return (res);
}

t_surface_coeffs	rotate_surface(t_surface *s)
{
	t_matrix33	m;

	s->angle = vector_sum(s->angle, s->cache.angle);
	m = fill_rot_m(s->angle);
	s->cache.angle = s->angle;
	s->angle = (t_dot){0, 0, 0};
	matrix_using(s->cache.c, m.m, &s->c);
	s->shift = s->cache.shift;
	s->cache.shift = (t_dot){0, 0, 0};
	s->c = surface_shift(s);
	return (s->c);
}

/*
** WEpainter enjoy typing
*/

void				matrix_using(t_surface_coeffs c, float m[3][3],\
t_surface_coeffs *res)
{
	res->a = m[0][0] * m[0][0] * c.a + m[1][0] * m[1][0] * c.b + m[2][0] *\
	m[2][0] * c.c + m[1][0] * m[2][0] * c.f2 + m[0][0] * m[2][0] * c.g2 +\
	m[0][0] * m[1][0] * c.h2;
	res->b = m[0][1] * m[0][1] * c.a + m[1][1] * m[1][1] * c.b + m[2][1] *\
	m[2][1] * c.c + m[1][1] * m[2][1] * c.f2 + m[0][1] * m[2][1] * c.g2 +\
	m[0][1] * m[1][1] * c.h2;
	res->c = m[0][2] * m[0][2] * c.a + m[1][2] * m[1][2] * c.b + m[2][2] *\
	m[2][2] * c.c + m[1][2] * m[2][2] * c.f2 + m[0][2] * m[2][2] * c.g2 +\
	m[0][2] * m[1][2] * c.h2;
	res->f2 = 2 * m[0][1] * m[0][2] * c.a + 2 * m[1][1] * m[1][2] * c.b +\
	m[2][1] * m[2][2] * c.c * 2 + m[1][1] * m[2][2] * c.f2 + m[0][1] *\
	m[2][2] * c.g2 + m[0][1] * m[1][2] * c.h2 + m[1][2] * m[2][1] * c.f2 +\
	m[0][2] * m[2][1] * c.g2 + m[0][2] * m[1][1] * c.h2;
	res->g2 = 2 * m[0][0] * m[0][2] * c.a + 2 * m[1][0] * m[1][2] * c.b +\
	m[2][0] * m[2][2] * c.c * 2 + m[1][0] * m[2][2] * c.f2 + m[0][0] *\
	m[2][2] * c.g2 + m[0][0] * m[1][2] * c.h2 + m[1][2] * m[2][0] * c.f2 +\
	m[0][2] * m[2][0] * c.g2 + m[0][2] * m[1][0] * c.h2;
	res->h2 = 2 * m[0][0] * m[0][1] * c.a + 2 * m[1][0] * m[1][1] * c.b +\
	m[2][0] * m[2][1] * c.c * 2 + m[1][0] * m[2][1] * c.f2 + m[0][0] *\
	m[2][1] * c.g2 + m[0][0] * m[1][1] * c.h2 + m[1][1] * m[2][0] * c.f2 +\
	m[0][1] * m[2][0] * c.g2 + m[0][1] * m[1][0] * c.h2;
	res->p2 = m[0][0] * c.p2 + m[1][0] * c.q2 + m[2][0] * c.r2;
	res->q2 = m[0][1] * c.p2 + m[1][1] * c.q2 + m[2][1] * c.r2;
	res->r2 = m[0][2] * c.p2 + m[1][2] * c.q2 + m[2][2] * c.r2;
	res->d = c.d;
}
