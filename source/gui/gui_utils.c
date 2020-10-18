/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:45:37 by root              #+#    #+#             */
/*   Updated: 2020/10/18 20:41:07 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_dot			get_position(int x_coord, t_gui_cache *gui_cache)
{
	t_dot position;

	position = (t_dot){0, 0, 0};
	if (!gui_cache->p_counter || gui_cache->p_counter > 200 ||\
	gui_cache->p_counter < -200)
		gui_cache->p_counter = 20;
	if (x_coord > 210 && x_coord < 230)
		position = (t_dot){0, 0, -(gui_cache->p_counter +\
		hypot(gui_cache->p_counter, 5))};
	else if (x_coord > 230 && x_coord < 255)
		position = (t_dot){-100, (gui_cache->p_counter -\
		sqrt(gui_cache->p_counter)), 0};
	else if (x_coord > 255 && x_coord < 275)
		position = (t_dot){(gui_cache->p_counter +\
		sqrtf(gui_cache->p_counter)), -100, 0};
	else if (x_coord > 275 && x_coord < 290)
		position = (t_dot){-200, -200, 0};
	gui_cache->p_counter += 25;
	return (position);
}

float			get_radius(int x_coord)
{
	float radius;

	radius = 0;
	if (x_coord > 210 && x_coord < 230)
		radius = 9999;
	else if (x_coord > 230 && x_coord < 255)
		radius = 25000;
	else if (x_coord > 255 && x_coord < 275)
		radius = 10000;
	else if (x_coord > 275 && x_coord < 290)
		radius = 50000;
	return (radius);
}

int				get_color(int x_coord)
{
	int color;

	color = 0;
	if (x_coord > 210 && x_coord < 230)
		color = RED;
	else if (x_coord > 230 && x_coord < 255)
		color = ORANGE;
	else if (x_coord > 255 && x_coord < 275)
		color = MINT;
	else if (x_coord > 275 && x_coord < 290)
		color = PURPLE;
	return (color);
}

void			get_light(int x_coord, t_sdl *sdl)
{
	if (x_coord > 210 && x_coord < 230)
		add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	else if (x_coord > 230 && x_coord < 255)
		add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
	else if (x_coord > 255 && x_coord < 275)
		add_light(&sdl->scene, (t_dot){300, 300, -1000}, 0.5);
	else if (x_coord > 275 && x_coord < 290)
		add_light(&sdl->scene, (t_dot){300, 100, -550}, 0.4);
}

/*
** gui_buttons control color, radius (for sphere), position for new objects.
** light has 4 fixed positions.
*/

void			gui_buttons(t_gui_cache *gui_cache, SDL_Event e, t_sdl *sdl)
{
	if (gui_cache->color != RED && gui_cache->color != ORANGE \
		&& gui_cache->color != MINT && gui_cache->color != PURPLE && \
		gui_cache->radius < 9999.0000)
	{
		gui_cache->radius = 10000;
		gui_cache->color = WHITE;
		gui_cache->position = (t_dot){-200, 0, 0};
	}
	if (e.button.x > 210 && e.button.x < 290)
	{
		if (e.button.y > 25 && e.button.y < 43)
			gui_cache->color = get_color(e.button.x);
		else if (e.button.y > 43 && e.button.y < 70)
			gui_cache->radius = get_radius(e.button.x);
		else if (e.button.y > 75 && e.button.y < 93)
			gui_cache->position = get_position(e.button.x, gui_cache);
		else if (e.button.y > 100 && e.button.y < 120)
			get_light(e.button.x, sdl);
	}
}

/*
** ДОПИЛИТЬ СТРУКТУРУ УДАЛЕНИЯ
*/
