/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:47:11 by root              #+#    #+#             */
/*   Updated: 2020/10/09 15:34:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"



void			button_create_sphere(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_sphere(&sdl->scene.conic, (t_surface){gui_cache->position, {1, 1, 1,\
	-(gui_cache->radius), 0, 0, 0, 0, 0, 0}, gui_cache->color, 100, 0.3, (t_dot){M_PI / 6, M_PI / 6, 0}, tmp, NULL});

//	add_sphere(&sdl->scene.sphere, (t_sphere){gui_cache->position, \
//	gui_cache->radius, gui_cache->color, 100, 0.3, \
//	NULL, NULL});

}

void 			gui_sphere(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	if ((e.button.x > 0 && e.button.x < 50))
		button_create_sphere(sdl, gui_cache);
}