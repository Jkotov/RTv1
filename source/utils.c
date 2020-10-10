/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:00:23 by epainter          #+#    #+#             */
/*   Updated: 2020/09/30 16:47:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

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
	t_gui_cache	*gui_cache;
//	uint		cur_time;
//	uint		time;

//	time = SDL_GetTicks();
	if (!(gui_cache = (t_gui_cache *)malloc(sizeof(t_gui_cache))))
		sdl_error ("GUI Alloc error");
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
				mouse_events(sdl, e, gui_cache);
		}
		render(sdl);
//		cur_time = SDL_GetTicks();
//		printf("%i ms on frame\n", cur_time - time);
//		time = cur_time;
	}
}
t_dot				rotate_vector(t_dot v, t_dot angle)
{
	float	m[3][3];
	t_dot	res;
	float	x;
	float	y;
	float	z;

	x = angle.x;
	y = angle.y;
	z = angle.z;
	m[0][0] = (cos(y + z) + cos(y - z)) / 2;
	m[0][1] = (-cos(x + y + z) + cos(x - y + z) - cos(x + y - z) +\
	cos(x - y - z) - 2 * sin(x + z) + 2 * sin(x - z)) / 4;
	m[0][2] = (-2 * cos(x + z) + 2 * cos(x - z) + sin(x + y + z) -\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m[1][0] = (sin(y + z) - sin(y - z)) / 2;
	m[1][1] = (2 * cos(x + z) + 2 * cos(x - z) - sin(x + y + z) +\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m[1][2] = (-cos(x + y + z) + cos(x - y + z) + cos(x + y - z) -\
	cos(x - y - z) - 2 * sin(x + z) - 2 * sin(x - z)) / 4;
	m[2][0] = -sin(y);
	m[2][1] = (sin(x + y) + sin(x - y)) / 2;
	m[2][2] = (cos(x + y) + cos(x - y)) / 2;
	res = (t_dot){v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],\
	v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2],\
	v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2]};
	return (res);
}

t_surface_coeffs	rotate_surface(t_surface *s)
{
	float	m[3][3];
	float	x;
	float	y;
	float	z;

	s->angle = vector_sum(s->angle, s->cache.angle);
	x = s->angle.x;
	y = s->angle.y;
	z = s->angle.z;
	m[0][0] = (cos(y + z) + cos(y - z)) / 2;
	m[0][1] = (-cos(x + y + z) + cos(x - y + z) - cos(x + y - z) +\
	cos(x - y - z) - 2 * sin(x + z) + 2 * sin(x - z)) / 4;
	m[0][2] = (-2 * cos(x + z) + 2 * cos(x - z) + sin(x + y + z) -\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m[1][0] = (sin(y + z) - sin(y - z)) / 2;
	m[1][1] = (2 * cos(x + z) + 2 * cos(x - z) - sin(x + y + z) +\
	sin(x - y + z) + sin(x + y - z) - sin(x - y - z)) / 4;
	m[1][2] = (-cos(x + y + z) + cos(x - y + z) + cos(x + y - z) -\
	cos(x - y - z) - 2 * sin(x + z) - 2 * sin(x - z)) / 4;
	m[2][0] = -sin(y);
	m[2][1] = (sin(x + y) + sin(x - y)) / 2;
	m[2][2] = (cos(x + y) + cos(x - y)) / 2;
	s->cache.angle = s->angle;
	s->angle = (t_dot){0, 0, 0};
	matrix_using(s->cache.c, m, &s->c);
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

t_surface_coeffs	surface_shift(t_surface *s)
{
	t_surface_coeffs res;

	res = s->c;
	res.p2 = s->c.p2 - s->c.g2 * s->shift.z - s->c.h2 * s->shift.y -\
	2 * s->c.a * s->shift.x;
	res.q2 = s->c.q2 - s->c.f2 * s->shift.z - s->c.h2 * s->shift.x -\
	2 * s->c.b * s->shift.y;
	res.r2 = s->c.r2 - s->c.f2 * s->shift.y - s->c.g2 * s->shift.x -\
	2 * s->c.c * s->shift.z;
	res.d = s->c.d + s->c.a * s->shift.x * s->shift.x + s->c.b * s->shift.y *\
	s->shift.y + res.c * s->shift.z * s->shift.z + s->c.f2 * s->shift.y *\
	s->shift.z + s->c.g2 * s->shift.x * s->shift.z + s->c.h2 * s->shift.x *\
	s->shift.y - s->c.p2 * s->shift.x - s->c.q2 * s->shift.y - s->c.r2 *\
	s->shift.z;
	s->cache.shift = vector_sum(s->shift, s->cache.shift);
	s->shift.x = 0;
	s->shift.y = 0;
	s->shift.z = 0;
	return (res);
}

t_dot				surface_normal(t_surface_coeffs c, t_dot dot)
{
	t_dot	res;

	res.x = 2 * c.a * dot.x + c.g2 * dot.z + c.h2 * dot.y + c.p2;
	res.y = 2 * c.b * dot.y + c.f2 * dot.z + c.h2 * dot.x + c.q2;
	res.z = 2 * c.c * dot.z + c.f2 * dot.y + c.g2 * dot.x + c.r2;
	res = vector_normalize(res);
	return (res);
}

void	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = src;
	while (i < (int)len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (src);
}
