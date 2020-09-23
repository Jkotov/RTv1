/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:00:23 by epainter          #+#    #+#             */
/*   Updated: 2020/09/23 12:59:00 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				quadratic_equation(t_dot coeffs, float *x1, float *x2)
{
	float	d;

	if (coeffs.x == 0)
		return (0);
	d = coeffs.y * coeffs.y - 4 * coeffs.x * coeffs.z;
	if (d < 0)
		return (0);
	if (d == 0)
	{
		*x1 = -coeffs.y * 0.5 / coeffs.x;
		*x2 = *x1;
		return (1);
	}
	d = sqrtf(d);
	*x1 = (-coeffs.y - d) * 0.5 / coeffs.x;
	*x2 = (-coeffs.y + d) * 0.5 / coeffs.x;
	return (2);
}

char			dot_cmp(t_dot d1, t_dot d2)
{
	if (d1.x == d2.x && d1.y == d2.y && d1.z == d2.z)
		return (1);
	return (0);
}

void			loop(t_sdl *sdl)
{
	SDL_Event	e;
	char		quit;
	uint		cur_time;
	uint		time;

	time = SDL_GetTicks();
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_KEYDOWN)
				keyboard_events(sdl, &quit, e);
			if (e.type == SDL_MOUSEBUTTONDOWN)
				mouse_events(sdl, e);
		}
		render(sdl);
		cur_time = SDL_GetTicks();
		printf("%i ms on frame\n", cur_time - time);
		time = cur_time;
	}
}

t_surface_coeffs	rotate_surface(t_dot angle, t_surface_coeffs c)
{
	float	m[3][3];

	m[0][0] = cos(angle.x) * cos(angle.z) - cos(angle.y) * sin(angle.x) *\
	sin(angle.z);
	m[0][1] = -cos(angle.z) * sin(angle.x) - cos(angle.x) * cos(angle.y) *\
	sin(angle.z);
	m[0][2] = sin(angle.y) * sin(angle.z);
	m[1][0] = cos(angle.y) * cos(angle.z) * sin(angle.x) + cos(angle.x) *\
	sin(angle.z);
	m[1][1] = cos(angle.x) * cos(angle.y) * cos(angle.z) - sin(angle.x) *\
	sin(angle.z);
	m[1][2] = -cos(angle.z) * sin(angle.y);
	m[2][0] = sin(angle.x) * sin(angle.y);
	m[2][1] = cos(angle.x) * sin(angle.y);
	m[2][2] = cos(angle.y);
	c = matrix_using(c, m);
	return (c);
}

/*
** WEpainter enjoy typing
*/

t_surface_coeffs	matrix_using(t_surface_coeffs c, float m[3][3])
{
	t_surface_coeffs	res;

	res.a = m[0][0] * m[0][0] * c.a + m[1][0] * m[1][0] * c.b + m[2][0] *\
	m[2][0] * c.c + m[1][0] * m[2][0] * c.f2 + m[0][0] * m[2][0] * c.g2 +\
	m[0][0] * m[1][0] * c.h2;
	res.b = m[0][1] * m[0][1] * c.a + m[1][1] * m[1][1] * c.b + m[2][1] *\
	m[2][1] * c.c + m[1][1] * m[2][1] * c.f2 + m[0][1] * m[2][1] * c.g2 +\
	m[0][1] * m[1][1] * c.h2;
	res.c = m[0][2] * m[0][2] * c.a + m[1][2] * m[1][2] * c.b + m[2][2] *\
	m[2][2] * c.c + m[1][2] * m[2][2] * c.f2 + m[0][2] * m[2][2] * c.g2 +\
	m[0][2] * m[1][2] * c.h2;
	res.f2 = 2 * m[0][1] * m[0][2] * c.a + 2 * m[1][1] * m[1][2] * c.b + m[2][1] *\
	m[2][2] * c.c * 2 + m[1][1] * m[2][2] * c.f2 + m[0][1] * m[2][2] * c.g2 +\
	m[0][1] * m[1][2] * c.h2 + m[1][2] * m[2][1] * c.f2 + m[0][2] * m[2][1] *\
	c.g2 + m[0][2] * m[1][1] * c.h2;
	res.g2 = 2 * m[0][0] * m[0][2] * c.a + 2 * m[1][0] * m[1][2] * c.b + m[2][0] *\
	m[2][2] * c.c * 2 + m[1][0] * m[2][2] * c.f2 + m[0][0] * m[2][2] * c.g2 +\
	m[0][0] * m[1][2] * c.h2 + m[1][2] * m[2][0] * c.f2 + m[0][2] * m[2][0] *\
	c.g2 + m[0][2] * m[1][0] * c.h2;
	res.h2 = 2 * m[0][0] * m[0][1] * c.a + 2 * m[1][0] * m[1][1] * c.b + m[2][0] *\
	m[2][1] * c.c * 2 + m[1][0] * m[2][1] * c.f2 + m[0][0] * m[2][1] * c.g2 +\
	m[0][0] * m[1][1] * c.h2 + m[1][1] * m[2][0] * c.f2 + m[0][1] * m[2][0] *\
	c.g2 + m[0][1] * m[1][0] * c.h2;
	res.p2 = m[0][0] * c.p2 + m[1][0] * c.q2 + m[2][0] * c.r2;
	res.q2 = m[0][1] * c.p2 + m[1][1] * c.q2 + m[2][1] * c.r2;
	res.r2 = m[0][2] * c.p2 + m[1][2] * c.q2 + m[2][2] * c.r2;
	res.d = c.d;
	return (res);
}

t_surface_coeffs	surface_shift(t_surface_coeffs c, t_dot *shift)
{
	t_surface_coeffs res;

	res = c;
	res.p2 = c.p2 - c.g2 * shift->z - c.h2 * shift->y - 2 * c.a * shift->x;
	res.q2 = c.q2 - c.f2 * shift->z - c.h2 * shift->x - 2 * c.b * shift->y;
	res.r2 = c.r2 - c.f2 * shift->y - c.g2 * shift->x - 2 * c.c * shift->z;
	res.d = c.d + c.a * shift->x * shift->x + c.b * shift->y * shift->y +\
	res.c * shift->z * shift->z + c.f2 * shift->y * shift->z + c.g2 * shift->x *\
	shift->z + c.h2 * shift->x * shift->y - c.p2 * shift->x - c.q2 * shift->y -\
	c.r2 * shift->z;
	shift->x = 0;
	shift->y = 0;
	shift->z = 0;
	return (res);
}

t_dot				surface_normal(t_surface_coeffs c, t_dot dot)
{
	t_dot	res;

	res.x = 2 * c.a * dot.x + c.g2 * dot.z + c.h2 * dot.y + c.p2;
	res.y = 2 * c.b * dot.y + c.f2 * dot.z + c.h2 * dot.x + c.q2;
	res.z = 2 * c.c * dot.z + c.f2 * dot.y + c.g2 * dot.x + c.r2;
	res = vector_normalize(res);
	return res;
}