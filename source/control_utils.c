/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:48:08 by root              #+#    #+#             */
/*   Updated: 2020/09/25 17:46:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void			mouse_events(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
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
				gui_sphere(sdl, e, gui_cache);
		else if (e.button.x > 100 && e.button.x < 210)
		{
//			gui_cone(sdl, e, gui_cache);
			printf("cone\n");
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
			gui_light(sdl, e, gui_cache);
			printf("light\n");
		}
	}
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
	sdl->scene.conic->c = surface_shift(sdl->scene.conic);
	if (e.key.keysym.sym == SDLK_q)
	{
		sdl->scene.conic->angle.z = M_PI / 6;
		sdl->scene.conic->c = rotate_surface(sdl->scene.conic);
	}
}
