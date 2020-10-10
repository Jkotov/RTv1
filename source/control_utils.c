/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:48:35 by epainter          #+#    #+#             */
/*   Updated: 2020/09/30 17:59:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		mouse_events(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	ray_tracing(sdl->scene, sdl->scene.camera.dir_vecs[e.button.y *\
	sdl->width + e.button.x], sdl->scene.camera.camera);

	gui_buttons(gui_cache, e);
	printf("color = %d\n position = {%f, %f, %f}\n, radius = %f\n", gui_cache->color, gui_cache->position.x, \
	gui_cache->position.y, gui_cache->position.z, gui_cache->radius);
	if ((e.button.x > 530 && e.button.x < 600) && (e.button.y > 0 && e.button.y < 65))
	{
//		set_default();
		printf("reset\n");
	}
	if (e.button.y > 50 && e.button.y < 65)
	{
		if ((e.button.x > 0 && e.button.x < 100))
//			printf("sphere\n");
			gui_sphere(sdl, e, gui_cache);
		else if (e.button.x > 100 && e.button.x < 210)
		{
			gui_cone(sdl, e, gui_cache);
//			printf("cone\n");
		}
		else if (e.button.x > 210 && e.button.x < 320)
		{
//			gui_plane(sdl, e, gui_cache);
			printf("plane\n");
		}
		else if (e.button.x > 320 && e.button.x < 420)
		{
//			gui_cylinder(sdl, e, gui_cache);
			printf("cylinder\n");
		}
		else if (e.button.x > 420 && e.button.x < 530)
		{
//			gui_light(sdl, e, gui_cache);
			printf("light\n");
		}
	}
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

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		*quit = 1;
	}
	if (e.key.keysym.sym == SDLK_RIGHT)
		sdl->scene.conic->shift.x = 10;
	if (e.key.keysym.sym == SDLK_LEFT)
		sdl->scene.conic->shift.x = -10;
	if (e.key.keysym.sym == SDLK_UP)
		sdl->scene.conic->shift.y = -10;
	if (e.key.keysym.sym == SDLK_DOWN)
		sdl->scene.conic->shift.y = 10;
	if (e.key.keysym.sym == SDLK_SPACE)
		sdl->scene.conic->shift.z = 10;
	camera_events(sdl, e);
	sdl->scene.conic->c = surface_shift(sdl->scene.conic);
	if (e.key.keysym.sym == SDLK_q)
	{
		sdl->scene.conic->angle.z = M_PI / 6;
		sdl->scene.conic->c = rotate_surface(sdl->scene.conic);
	}
}
