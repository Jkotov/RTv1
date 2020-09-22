/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:52:59 by root              #+#    #+#             */
/*   Updated: 2020/09/22 15:15:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void 			del_light(t_light **list)
{
	while ((*list)->next)
		list = &(*list)->next;
	free(*list);
	*list = NULL;
}

int 			count_light(t_light *list)
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

void 			gui_light(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	if ((e.button.x > 420 && e.button.x < 475))
		add_light(&sdl->scene, gui_cache->position, 0.4);
	else if (e.button.x > 475 && e.button.x < 530)
	{
		if (count_light(sdl->scene.light) != 0)
			del_light(&sdl->scene.light);
	}
}