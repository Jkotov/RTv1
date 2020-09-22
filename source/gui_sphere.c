/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:47:11 by root              #+#    #+#             */
/*   Updated: 2020/09/22 14:57:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void 			del_sphere(t_sphere **list)
{
	while ((*list)->next)
		list = &(*list)->next;
	free(*list);
	*list = NULL;
}

int 			count_spheres(t_sphere *list)
{
	int 		i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	return(i);
}

void			button_create_sphere(t_sdl *sdl, t_gui_cache *gui_cache)
{
	add_sphere(&sdl->scene.sphere, (t_sphere){gui_cache->position, \
	gui_cache->radius, gui_cache->color, 100, 0.3, \
	NULL, NULL});

}

void 			gui_sphere(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	if ((e.button.x > 0 && e.button.x < 50))
		button_create_sphere(sdl, gui_cache);
	else if (e.button.x > 50 && e.button.x < 100)
	{
		if (count_spheres(sdl->scene.sphere) != 0)
			del_sphere(&sdl->scene.sphere);
	}
}