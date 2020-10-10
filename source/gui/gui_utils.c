/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:45:37 by root              #+#    #+#             */
/*   Updated: 2020/10/09 15:35:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_dot			get_position(int x_coord, t_gui_cache *gui_cache)
{
	t_dot position;

	position = (t_dot){0,0,0};
	if (!gui_cache->p_counter || gui_cache->p_counter > 200 || gui_cache->p_counter < -200)
		gui_cache->p_counter = 20;
	if (x_coord > 319 && x_coord < 367)
		position = (t_dot){0, 0, -(gui_cache->p_counter + hypot(gui_cache->p_counter, 5))};
	else if (x_coord > 372 && x_coord < 419)
		position = (t_dot){-100, (gui_cache->p_counter - sqrt(gui_cache->p_counter)), 0};
	else if (x_coord > 424 && x_coord < 473)
		position = (t_dot){(gui_cache->p_counter + sqrt(gui_cache->p_counter)), -100, 0};
	else if (x_coord > 478 && x_coord < 526)
		position = (t_dot){-200, -200, 0};
	gui_cache->p_counter += 25;
	printf("p_counter = %f\n", gui_cache->p_counter);
	return (position);
}

float 			get_radius(int x_coord)
{
	float  radius;

	radius = 0;
	if (x_coord > 108 && x_coord < 157)
		radius = 9999;
	else if (x_coord > 157 && x_coord < 210)
		radius = 25000;
	else if (x_coord > 210 && x_coord < 260)
		radius = 10000;
	else if (x_coord > 260 && x_coord < 316)
		radius = 50000;
	return (radius);
}

int				get_color(int x_coord)
{
	int 	color;

	color = 0;
	if (x_coord > 108 && x_coord < 157)
		color = RED;
	else if (x_coord > 157 && x_coord < 210)
		color = ORANGE;
	else if (x_coord > 210 && x_coord < 260)
		color = MINT;
	else if (x_coord > 260 && x_coord < 316)
		color = PURPLE;
	return (color);
}

void			gui_buttons(t_gui_cache *gui_cache, SDL_Event e)
{
	if (gui_cache->color != RED && gui_cache->color != ORANGE \
		&& gui_cache->color != MINT && gui_cache->color != PURPLE && \
		gui_cache->radius < 50.0000 && gui_cache->position.x < 100.0000)
	{
		gui_cache->radius = 80;
		gui_cache->color = WHITE;
		gui_cache->position = (t_dot){400, 200, 300};
	}
	if (e.button.x < 316 && e.button.y > 80 && e.button.y < 105)
	{
//		colors
		gui_cache->color = get_color(e.button.x);
	}
	else if (e.button.y > 70 && e.button.y < 85)
	{
//		radius
		gui_cache->radius = get_radius(e.button.x);
	}
	else if (e.button.x > 300 && e.button.y > 90 && e.button.y < 102)
	{
//		position
		gui_cache->position = get_position(e.button.x, gui_cache);
	}
}

