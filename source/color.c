/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:23:47 by epainter          #+#    #+#             */
/*   Updated: 2020/10/01 22:35:43 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					color_intens(int color, float intens)
{
	return ((int)(((color & 0xFF000000) >> 24) * intens) << 24) +\
	((int)(((color & 0xFF0000) >> 16) * intens) << 16) +\
	((int)(((color & 0xFF00) >> 8) * intens) << 8) +\
	((int)(((color & 0xFF) * intens)));
}

int					color_sum(int c1, int c2)
{
	int	a;
	int r;
	int g;
	int b;

	a = (int)(((c1 & 0xFF000000) >> 24)\
	+ ((c2 & 0xFF000000) >> 24)) << 24;
	r = (int)(((c1 & 0xFF0000) >> 16) + ((c2 & 0xFF0000) >> 16)) << 16;
	g = (int)(((c1 & 0xFF00) >> 8) + ((c2 & 0xFF00) >> 8)) << 8;
	b = (int)(c1 & 0xFF) + (c2 & 0xFF);
	a = a > (int)0xFF000000 ? (int)0xFF000000 : (int)a;
	r = r > (int)0xFF0000 ? 0xFF0000 : r;
	g = g > (int)0xFF00 ? 0xFF00 : g;
	b = b > (int)0xFF ? 0xFF : b;
	return a + r + g + b;
}

t_compute_light_p	init_light_params(t_dot dir_vec, int len,\
t_surface *sphere, t_dot start)
{
	t_compute_light_p	light_p;

	light_p.dot = vector_sum(vector_mult_num(dir_vec, len - len * 0.001), start);
	light_p.specular = sphere->specular;
	light_p.direction_vec = vector_mult_num(dir_vec, -1);
	light_p.normal_vec = surface_normal(sphere->c, light_p.dot);
	return (light_p);
}

int					ray_tracing(t_rt rt)
{
	int					color;
	float				len;
	t_surface			*cur_sphere;
	t_compute_light_p	light_p;

	color = 0;
	len = INFINITY;
	cur_sphere = closest(rt.start, rt.dir_vec, rt.scene, &len);
	if (!isinf(len) && rt.scene.light)
	{
		light_p = init_light_params(rt.dir_vec, len, cur_sphere, rt.start);
		color = color_intens(cur_sphere->color, lighting(rt.scene, light_p));
		if (rt.scene.cur_depth++ < rt.scene.max_depth)
		{
			color = color_sum(color_intens(color,\
			(1 - cur_sphere->reflective)),\
			color_intens(ray_tracing((t_rt){rt.scene,\
			vector_reflection(rt.dir_vec, light_p.normal_vec),\
			light_p.dot}), cur_sphere->reflective));
		}
	}
	return (color);
}

void				render(t_sdl *sdl)
{
	int		x;
	int		y;
	t_rt	rt;

	SDL_LockTexture(sdl->fg, NULL, (void**)&sdl->buffer, &sdl->buffer_len);
	x = -1;
	y = -1;
	while (++x < sdl->width)
	{
		while (++y < sdl->height)
		{
			rt.scene = sdl->scene;
			rt.start = sdl->scene.camera.camera;
			rt.dir_vec = sdl->scene.camera.dir_vecs[y * sdl->width + x];
			sdl->scene.cur_depth = 0;
			sdl->buffer[y * sdl->width + x] = ray_tracing(rt);
		}
		y = -1;
	}
	SDL_UnlockTexture(sdl->fg);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->fg, NULL, NULL);
	//SDL_RenderCopy(sdl->renderer, sdl->menu.img, NULL, &sdl->menu.menu_size);
	SDL_RenderPresent(sdl->renderer);
}
