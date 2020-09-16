/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:45:44 by epainter          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
=======
/*   Updated: 2020/09/16 15:18:06 by root             ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void			init_menu(t_sdl *sdl)
{
	sdl->menu.menu_size = (SDL_Rect){0, 0, sdl->width, 30};
	sdl->menu.img = create_texture("menu.png", sdl);
	sdl->menu.add_menu_size = (SDL_Rect){450, 100, 150, 350};
	sdl->menu.add_menu = create_texture("add_coords.png", sdl);
}

t_sdl		sdl_init(void)
{
	t_sdl		sdl;

	sdl.width = 640;
	sdl.height = 480;
	scene_init(&sdl);
	sdl.buffer_len = sdl.width * sdl.height;
	sdl.window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED\
	, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (SDL_Init(0) != 0)
		sdl_error("SDL_Init Error: ");
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

void		scene_init(t_sdl *sdl)
{
	sdl->scene.camera = (t_dot){(float)sdl->width\
	/ 2, (float)sdl->height / 2, -1000};
	sdl->scene.clipping_plane = 500;
	sdl->scene.sphere = NULL;
	sdl->scene.light = NULL;
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){300, 250, 150},\
	150, 0xFF00, 100, 0.3, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){400, 250, 150},\
	100, 0xFF, 75, 0.5, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){100, 250, 150},\
	125, 0xFF0000, 10, 1, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){300, 5375, 150},\
	5000, 0xFFFF00, 10, 0.1, NULL});
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.5);
	add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	add_light(&sdl->scene, (t_dot){300, 100, 550}, 0.4);
}