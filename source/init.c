/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:45:44 by epainter          #+#    #+#             */
/*   Updated: 2020/09/24 14:48:49 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			init_menu(t_sdl *sdl)
{
	sdl->menu.menu_size = (SDL_Rect){0, 0, sdl->width, 30};
	sdl->menu.img = create_texture("menu.png", sdl);
	sdl->menu.add_menu_size = (SDL_Rect){450, 100, 150, 350};
	sdl->menu.add_menu = create_texture("add_coords.png", sdl);
}

t_sdl			sdl_init(void)
{
	t_sdl		sdl;

	sdl.width = 640;
	sdl.height = 480;
	sdl.buffer_len = sdl.width * sdl.height;
	scene_init(&sdl);
	if (SDL_Init(0) != 0)
		sdl_error("SDL_Init Error: ");
	sdl.window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED\
	, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_InitSubSystem(SDL_INIT_EVENTS);
	if (sdl.window == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1,\
	0);
	if (sdl.renderer == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		ft_putstr("IMG_Init");
		SDL_Quit();
	}
	return (sdl);
}

t_dot			*directions_vec_compute(t_sdl *sdl)
{
	t_dot	*dir_vecs;
	int		x;
	int		y;

	if ((dir_vecs = (t_dot*)malloc(sizeof(t_dot) * sdl->buffer_len)) == NULL)
		sdl_error("Alloc error");
	x = -1;
	y = -1;
	while (++x < sdl->width)
	{
		while (++y < sdl->height)
		{
			dir_vecs[y * sdl->width + x] =\
			vector_normalize(vector_subtraction((t_dot){x, y, 0},\
			sdl->scene.camera));
		}
		y = -1;
	}
	return (dir_vecs);
}

void			scene_init(t_sdl *sdl)
{
	t_surface_cache tmp;

	sdl->scene.camera = (t_dot){(float)sdl->width\
	/ 2, (float)sdl->height / 2, -1000};
	sdl->scene.clipping_plane = 500;
	sdl->scene.max_depth = 3;
	sdl->scene.dir_vecs = directions_vec_compute(sdl);
	sdl->scene.conic = NULL;
	sdl->scene.light = NULL;
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){0, 0, 00},\
    {1, 2, 0, -10000, 0, 0, 0, 0, 0, 0}, 0xFF00, 100, 0.3, (t_dot){0, 0, 0}, tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){300, 300, 50},\
    {1, 2, 1, -20000, 0, 0, 0, 0, 0, 0}, 0xFF, 100, 0.3, (t_dot){0, 0, 0}, tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){100, 100, 100},\
    {1, 2, -1, 0, 0, 0, 0, 0, 0, 0}, 0xFF0000, 50, 0.3, (t_dot){0, M_PI / 3, 0}, tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){100, 100, 1000},\
    {0, 0, 0, -100, 0, 0, 0, 1, 2, 3}, 0xFFFFF0, 50, 0, (t_dot){0, M_PI_2, 0}, tmp, NULL});
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
//	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.5);
	add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	add_light(&sdl->scene, (t_dot){300, 100, 550}, 0.4);
}
