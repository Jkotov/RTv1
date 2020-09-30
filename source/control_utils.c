/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:48:08 by root              #+#    #+#             */
/*   Updated: 2020/09/25 10:51:40 by root             ###   ########.fr       */
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
	t_dot tmp;

	if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		*quit = 1;
	}
//	if (e.key.keysym.sym == SDLK_l)
//	{
//		printf("btn down\n");
//	}
	if (e.key.keysym.sym == SDLK_SPACE)
		sdl->scene.sphere->center.z++;
	if (e.key.keysym.sym == SDLK_a)
	{
		while (e.button.type != SDL_MOUSEBUTTONDOWN)
			SDL_PollEvent(&e);
		tmp = (t_dot){e.button.x, e.button.y, 300};
		e.button.type = 0;
		while (e.button.type != SDL_MOUSEBUTTONDOWN)
			SDL_PollEvent(&e);
		add_sphere(&sdl->scene.sphere, (t_sphere){tmp,\
		abs_vector(vector_subtraction((t_dot){e.button.x, e.button.y, 300},\
		tmp)), 0xFF00, 100, 0.3, NULL, NULL});
	}
}