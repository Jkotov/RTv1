/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:00:23 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 07:33:13 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int					quadratic_equation(t_dot coeffs, float *x1, float *x2)
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

void				loop(t_sdl *sdl)
{
	SDL_Event	e;
	char		quit;
	t_gui_cache	*gui_cache;
	t_surface	*head;
//	uint		cur_time;
//	uint		time;

//	time = SDL_GetTicks();
	if (!(gui_cache = (t_gui_cache *)malloc(sizeof(t_gui_cache))))
		sdl_error("GUI Alloc error");
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_KEYDOWN)
			{
//				printf("keydown");
//				last_shape(&sdl->scene.shape);
				keyboard_events(sdl, &quit, e);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
				mouse_events(sdl, e, gui_cache);
		}
		head = sdl->scene.shape;
//		give_number(&sdl->scene.shape);
//		while(sdl->scene.shape->next)
//		{
//			printf("shape number is: %i\n", sdl->scene.shape->number);
//			sdl->scene.shape = sdl->scene.shape->next;
//		}
//		printf("shape number is: %i\n", sdl->scene.shape->number);
		sdl->scene.shape = head;
		render(sdl);
//		cur_time = SDL_GetTicks();
//		printf("%i ms on frame\n", cur_time - time);
//		time = cur_time;
	}
	free(gui_cache);
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

void				*ft_memset(void *src, int c, size_t len)
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
