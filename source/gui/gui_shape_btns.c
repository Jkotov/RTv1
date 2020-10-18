/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_shape_btns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:31:17 by epainter          #+#    #+#             */
/*   Updated: 2020/10/18 20:31:17 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void			button_create_cylinder(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_shape(&sdl->scene.shape, (t_surface){gui_cache->position, {1, 2, 0,\
	-10000, 0, 0, 0, 0, 0, 0}, gui_cache->color, \
	100, 0.3, (t_dot){M_PI / 6, M_PI / 6, 0}, tmp, 0, NULL});
}

void			button_create_plane(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_shape(&sdl->scene.shape, (t_surface){gui_cache->position,\
	{0, 0, 0, -100, 0, 0, 0, 1, 2, 3}, \
	gui_cache->color, 50, 0, (t_dot){0, M_PI_2, 0}\
	, tmp, 0, NULL});
}

void			button_create_cone(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_shape(&sdl->scene.shape, (t_surface){gui_cache->position, {1, 2,\
	-1, 0, 0, 0, 0, 0, 0, 0}, gui_cache->color, \
	10, 0.3, (t_dot){0, M_PI_2, 0},\
	tmp, 0, NULL});
}

void			button_create_sphere(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_shape(&sdl->scene.shape, (t_surface){gui_cache->position, {1, 1, 1,\
	-(gui_cache->radius), 0, 0, 0, 0, 0, 0}, gui_cache->color, \
	100, 0.3, (t_dot){M_PI / 6, M_PI / 6, 0}, tmp, 0, NULL});
}
