/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:48:35 by epainter          #+#    #+#             */
/*   Updated: 2020/10/18 21:16:44 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		mouse_events(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	gui_buttons(gui_cache, e, sdl);
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
			ft_putstr("reset");
		else if (e.button.y > 21 && e.button.y < 43)
		{
			if (count_objs(sdl->scene.shape) != 3)
				del_objs(&sdl->scene.shape);
		}
	}
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

void		get_counter(t_sdl *sdl, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_0)
	{
		if (sdl->scene.shape->next == NULL)
			sdl->counter = sdl->scene.shape->number;
		else
			sdl->counter += 1;
	}
	if (e.key.keysym.sym == SDLK_1)
	{
		ft_putstr("key down"); // Wow
		if (sdl->counter - 1 < 0)
			sdl->counter = 0;
		else
			sdl->counter--;
	}
}

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e)
{
	t_surface	*head;

	head = sdl->scene.shape;
	get_counter(sdl, e);
	sdl->scene.shape = select_last(&sdl->scene.shape, sdl->counter);
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
	camera_events(sdl, e.key.keysym.sym);
	sdl->scene.shape->c = surface_shift(sdl->scene.shape);
	if (e.key.keysym.sym == SDLK_q)
	{
		sdl->scene.shape->angle.z = M_PI / 6;
		sdl->scene.shape->c = rotate_surface(sdl->scene.shape);
	}
	sdl->scene.shape = head;
}
