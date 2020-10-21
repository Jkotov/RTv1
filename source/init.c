/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:45:44 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 23:43:17 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_sdl			sdl_init(void)
{
	t_sdl		sdl;

	sdl.scene_file = NULL;
	sdl.width = 640;
	sdl.height = 480;
	sdl.buffer_len = sdl.width * sdl.height;
	scene_init(&sdl);
	if (SDL_Init(0) != 0)
		sdl_error("SDL_Init Error: ");
	sdl.window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED\
	, SDL_WINDOWPOS_CENTERED, sdl.width, sdl.height, SDL_WINDOW_SHOWN);
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

void			camera_init(t_sdl *sdl)
{
	sdl->scene.camera.x_vec = (t_dot){1, 0, 0};
	sdl->scene.camera.y_vec = (t_dot){0, 1, 0};
	sdl->scene.camera.angle = (t_dot){0, 0, 0};
	sdl->scene.camera.camera = (t_dot){0, 0, -1000};
	sdl->scene.camera.center_vec = (t_dot){0, 0, 1};
	sdl->scene.camera.dir_vecs = NULL;
	camera_move(sdl);
}

/*
** 1 fig - cylinder
** 2 fig - ellipsoid
** 3 fig - conic
** 4 fig - plane
*/

void			set_default_scene(t_sdl *sdl)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_shape(&sdl->scene.shape, (t_surface){(t_dot){300, 200, 0}, {1, 2, 0,\
	-10000, 0, 0, 0, 0, 0, 0}, 0xFF00, 100, 0.3, \
	(t_dot){M_PI / 6, M_PI / 6, 0}, tmp, 0, NULL});
	add_shape(&sdl->scene.shape, (t_surface){(t_dot){300, 100, 300}, {1, 2, 1,\
	-20000, 0, 0, 0, 0, 0, 0}, 0xFF, 100, 0.3, \
	(t_dot){0, 0, 0}, tmp, 0, NULL});
	add_shape(&sdl->scene.shape, (t_surface){(t_dot){100, 100, 100}, {1, 2,\
	-1, 0, 0, 0, 0, 0, 0, 0}, 0xFF0000, 50, 0.3, \
	(t_dot){0, M_PI / 3, 0}, tmp, 0, NULL});
	add_shape(&sdl->scene.shape, (t_surface){(t_dot){100, 100, 1000},\
	{0, 0, 0, -100, 0, 0, 0, 1, 2, 3}, 0xFFFFF0, 50,\
	0, (t_dot){0, M_PI_2, 0}, tmp, 0, NULL});
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
	add_light(&sdl->scene, (t_dot){300, 300, -1000}, 0.5);
	add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	add_light(&sdl->scene, (t_dot){300, 100, -550}, 0.4);
}

void			scene_init(t_sdl *sdl)
{
	camera_init(sdl);
	sdl->scene.max_depth = 3;
	sdl->scene.shape = NULL;
	sdl->scene.light = NULL;
	sdl->need_render = 1;
}
