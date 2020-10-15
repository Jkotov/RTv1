/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:48:35 by epainter          #+#    #+#             */
/*   Updated: 2020/10/15 18:34:29 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_surface	*mouse_events(t_sdl *sdl, SDL_Event e)
{
	float tmp;

	tmp = INFINITY;
	return (closest(sdl->scene.camera.camera, sdl->scene.camera.dir_vecs[e.button.y * sdl->width + e.button.x], sdl->scene, &tmp));
}

void		camera_events(t_sdl *sdl, SDL_Event e)
{
	char	flag;
	t_dot	tmp;

	flag = 0;
	tmp = vector_mult_num(sdl->scene.camera.center_vec, 100);
	if (e.key.keysym.sym == SDLK_w)
	{
		flag = 1;
		sdl->scene.camera.camera = vector_sum(sdl->scene.camera.camera, tmp);
	}
	if (e.key.keysym.sym == SDLK_s)
	{
		flag = 1;
		sdl->scene.camera.camera = vector_subtraction(sdl->scene.camera.camera, tmp);
	}
	if (e.key.keysym.sym == SDLK_a)
	{
		flag = 1;
		sdl->scene.camera.angle.y -= M_PI / 60;
	}
	if (e.key.keysym.sym == SDLK_d)
	{
		flag = 1;
		sdl->scene.camera.angle.y += M_PI / 60;
	}
	if (e.key.keysym.sym == SDLK_e)
	{
		flag = 1;
		sdl->scene.camera.angle.x += M_PI / 120;
	}
	if (e.key.keysym.sym == SDLK_c)
	{
		flag = 1;
		sdl->scene.camera.angle.x -= M_PI / 120;
	}
	if (e.key.keysym.sym == SDLK_z)
	{
		flag = 1;
		sdl->scene.camera.angle.z -= M_PI / 60;
	}
	if (e.key.keysym.sym == SDLK_x)
	{
		flag = 1;
		sdl->scene.camera.angle.z += M_PI / 60;
	}
	if (flag)
		camera_move(sdl);
}

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e, t_surface *cur)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		*quit = 1;
	}
	if (e.key.keysym.sym == SDLK_RIGHT && cur)
		cur->shift.x = 10;
	if (e.key.keysym.sym == SDLK_LEFT && cur)
		cur->shift.x = -10;
	if (e.key.keysym.sym == SDLK_UP && cur)
		cur->shift.y = -10;
	if (e.key.keysym.sym == SDLK_DOWN && cur)
		cur->shift.y = 10;
	if (e.key.keysym.sym == SDLK_SPACE && cur)
		cur->shift.z = 10;
	camera_events(sdl, e);
	if (cur)
		cur->c = surface_shift(cur);
	if (e.key.keysym.sym == SDLK_q && cur)
	{
		cur->angle.z = M_PI / 6;
		cur->c = rotate_surface(cur);
	}
}
