/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:41:28 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 11:47:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void			reset(t_sdl *sdl)
{
	clean_scene(&sdl->scene);
	if (sdl->scene_file)
		parsing(sdl, sdl->scene_file);
	else
		set_default_scene(sdl);
}

void			del_surface(t_sdl *sdl, t_surface *del)
{
	t_surface *tmp;

	tmp = sdl->scene.shape;
	if (!tmp || !del)
		return ;
	if (tmp == del)
	{
		sdl->scene.shape = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp->next)
	{
		if (tmp->next == del)
		{
			tmp->next = tmp->next->next;
			free(del);
			return ;
		}
		tmp = tmp->next;
	}
}

void			init_menu(t_sdl *sdl)
{
	sdl->menu.menu_size = (SDL_Rect){0, 0, sdl->width, 300};
	sdl->menu.img = create_texture("menu.png", sdl);
}
