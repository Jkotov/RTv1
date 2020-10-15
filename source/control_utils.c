/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:48:35 by epainter          #+#    #+#             */
/*   Updated: 2020/10/15 15:30:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		mouse_events(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
//	cur_shape = sdl->scene.shape->cache;
	ray_tracing(sdl->scene, sdl->scene.camera.dir_vecs[e.button.y *\
	sdl->width + e.button.x], sdl->scene.camera.camera);
	gui_buttons(gui_cache, e, sdl);
	if (e.button.y > 120)
	{
		sdl->scene.shape = closest(sdl->scene.camera.camera, \
		sdl->scene.camera.dir_vecs[e.button.y * sdl->width + e.button.x], \
		sdl->scene, &sdl->scene.camera.camera.z);
		printf("x = %d\n y %d\n", e.button.x, e.button.y);
	}

//	printf("e.b.x = %d\n e.b.y = %d\n", e.button.x, e.button.y);
//	printf("color = %d\n position = {%f, %f, %f}\n, radius = %f\n", gui_cache->color, gui_cache->position.x, \
//	gui_cache->position.y, gui_cache->position.z, gui_cache->radius);
	if (e.button.x > 0 && e.button.x < 105)
	{
		if (e.button.y > 3 && e.button.y < 45)
			button_create_sphere(sdl, gui_cache);
		else if (e.button.y > 50 && e.button.y < 70)
			button_create_cone(sdl, gui_cache);
		else if (e.button.y > 75 && e.button.y < 92)
			button_create_plane(sdl, gui_cache);
		else if (e.button.y > 99 && e.button.y < 118)
			button_create_cylinder(sdl, gui_cache);
	}
	else if (e.button.x > 290 && e.button.x < 395)
	{
		if (e.button.y > 3 && e.button.y < 20)
			printf("reset");
		else if (e.button.y > 21 && e.button.y < 43)
		{
			if (count_objs(sdl->scene.shape) != 3)
				del_objs(&sdl->scene.shape);
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
		*quit = 1;
	if (e.key.keysym.sym == SDLK_RIGHT)
		sdl->scene.shape->shift.x = 10;
	if (e.key.keysym.sym == SDLK_LEFT)
		sdl->scene.shape->shift.x = -10;
	if (e.key.keysym.sym == SDLK_UP)
		sdl->scene.shape->shift.y = -10;
	if (e.key.keysym.sym == SDLK_DOWN)
		sdl->scene.shape->shift.y = 10;
	if (e.key.keysym.sym == SDLK_SPACE)
		sdl->scene.shape->shift.z = 10;
	if (e.key.keysym.sym == SDLK_SLASH)
		sdl->scene.shape->shift.z = -10;
	camera_events(sdl, e);
	sdl->scene.shape->c = surface_shift(sdl->scene.shape);
	if (e.key.keysym.sym == SDLK_q)
	{
		sdl->scene.shape->angle.z = M_PI / 6;
		sdl->scene.shape->c = rotate_surface(sdl->scene.shape);
	}
}
