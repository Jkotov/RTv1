/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:48:35 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 23:56:15 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

/*
** e.wheel.x = 0 ; e.wheel.y = -1 - zoom +
** e.wheel.x = 0 ; e.wheel.y = 1 - xoom -
*/

void		mouse_camera(t_sdl *sdl, SDL_Event e)
{
	t_dot	tmp;

	tmp = vector_mult_num(sdl->scene.camera.center_vec, 100);
	if (e.wheel.y == -1)
		sdl->scene.camera.camera = vector_sum(sdl->scene.camera.camera, tmp);
	if (e.wheel.y == 1)
		sdl->scene.camera.camera = vector_sub(sdl->scene.camera.camera, tmp);
	camera_move(sdl);
}

void		camera_events(t_sdl *sdl, SDL_Keycode sym)
{
	t_dot	tmp;

	tmp = vector_mult_num(sdl->scene.camera.center_vec, 100);
	if (sym == SDLK_w)
		sdl->scene.camera.camera = vector_sum(sdl->scene.camera.camera, tmp);
	if (sym == SDLK_s)
		sdl->scene.camera.camera = vector_sub(sdl->scene.camera.camera, tmp);
	if (sym == SDLK_a)
		sdl->scene.camera.angle.y -= M_PI / 60;
	if (sym == SDLK_d)
		sdl->scene.camera.angle.y += M_PI / 60;
	if (sym == SDLK_e)
		sdl->scene.camera.angle.x += M_PI / 120;
	if (sym == SDLK_c)
		sdl->scene.camera.angle.x -= M_PI / 120;
	if (sym == SDLK_z)
		sdl->scene.camera.angle.z -= M_PI / 60;
	if (sym == SDLK_x)
		sdl->scene.camera.angle.z += M_PI / 60;
	if (sym == SDLK_w || sym == SDLK_s || sym == SDLK_a || sym == SDLK_d ||\
	sym == SDLK_e || sym == SDLK_c || sym == SDLK_z || sym == SDLK_x)
		camera_move(sdl);
}

void		del_reset(t_sdl *sdl, SDL_Event e, t_surface *cur)
{
	if (e.button.y > 3 && e.button.y < 20)
	{
		sdl->need_render = 1;
		reset(sdl);
	}
	else if (e.button.y > 21 && e.button.y < 43)
	{
		del_surface(sdl, cur);
		sdl->need_render = 1;
	}
}

t_surface	*mouse_events(t_sdl *sdl, SDL_Event e,\
t_gui_cache *gui_cache, t_surface *cur)
{
	float	tmp;

	tmp = INFINITY;
	gui_buttons(gui_cache, e, sdl);
	if (e.wheel.x == 0 && (e.wheel.y == -1 || e.wheel.y == 1))
		mouse_camera(sdl, e);
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
		del_reset(sdl, e, cur);
	return (closest(sdl->scene.camera.camera, \
	sdl->scene.camera.dir_vecs[e.button.y * sdl->width \
	+ e.button.x], sdl->scene, &tmp));
}

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e, t_surface *cur)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
		*quit = 1;
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
	if (e.key.keysym.sym == SDLK_SLASH && cur)
		cur->shift.z = -10;
	camera_events(sdl, e.key.keysym.sym);
	if (cur)
		cur->c = surface_shift(cur);
	if (e.key.keysym.sym == SDLK_q && cur)
	{
		cur->angle.z = M_PI / 6;
		cur->c = rotate_surface(cur);
	}
}
