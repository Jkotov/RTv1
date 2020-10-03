/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:45:44 by epainter          #+#    #+#             */
/*   Updated: 2020/10/02 01:40:37 by epainter         ###   ########.fr       */
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

	sdl.width = 100;
	sdl.height = 100;
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

t_dot			*directions_vec_compute(t_sdl *sdl)
{
	t_camera	tmp;
	t_dot		*dir_vecs;
	int			x;
	int			y;
	t_dot		screen_dot;

	tmp = sdl->scene.camera;
	if ((dir_vecs = (t_dot*)malloc(sizeof(t_dot) * sdl->width * sdl->height)) == NULL)
		sdl_error("Alloc error");
	x = -1;
	y = -1;
	while (++x < sdl->width)
	{
		while (++y < sdl->height)
		{
			screen_dot = vector_sum(tmp.screen_center, vector_mult_num(tmp.x_screen_vec, -sdl->width / 2 + x));
			screen_dot = vector_sum(screen_dot, vector_mult_num(tmp.y_screen_vec, -sdl->height / 2 + y));
			dir_vecs[y * sdl->width + x] =\
			vector_normalize(vector_subtraction(screen_dot,\
			tmp.camera));
		}
		y = -1;
	}
	return (dir_vecs);
}

void			camera_move(t_sdl *sdl)
{
	t_camera	tmp;

	tmp = sdl->scene.camera;
	tmp.center_vec = vector_normalize(rotate_vector((t_dot){0, 0, 1}, tmp.angle));
	tmp.screen_center = vector_sum(vector_mult_num(tmp.center_vec, 1000), tmp.camera);
	tmp.x_screen_vec = vector_normalize(rotate_vector((t_dot){1, 0, 0}, tmp.angle));
	tmp.y_screen_vec = vector_normalize(rotate_vector((t_dot){0, 1, 0}, tmp.angle));
	sdl->scene.camera = tmp;
	free(tmp.dir_vecs);
	sdl->scene.camera.dir_vecs = directions_vec_compute(sdl);
}

void			camera_init(t_sdl *sdl)
{
	sdl->scene.camera.x_screen_vec = (t_dot){1, 0, 0};
	sdl->scene.camera.y_screen_vec = (t_dot){0, 1, 0};
	sdl->scene.camera.angle = (t_dot){0, 0, 0};
	sdl->scene.camera.camera = (t_dot){0, 0, -1000};
	sdl->scene.camera.center_vec = (t_dot){0, 0, 1};
	sdl->scene.camera.dir_vecs = NULL;
	camera_move(sdl);
}

void			scene_init(t_sdl *sdl)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	camera_init(sdl);
	sdl->scene.max_depth = 0;
	sdl->scene.conic = NULL;
	sdl->scene.light = NULL;
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){300, 200, 0}, {1, 2, 0,\
	-10000, 0, 0, 0, 0, 0, 0}, 0xFF00, 100, 0.3, (t_dot){M_PI / 6, M_PI / 6, 0}, tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){300, 100, 300}, {1, 2, 1,\
	-20000, 0, 0, 0, 0, 0, 0}, 0xFF, 100, 0.3, (t_dot){0, 0, 0}, tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){100, 100, 100}, {1, 2,\
	-1, 0, 0, 0, 0, 0, 0, 0}, 0xFF0000, 50, 0.3, (t_dot){0, M_PI / 3, 0},\
	tmp, NULL});
	add_sphere(&sdl->scene.conic, (t_surface){(t_dot){100, 100, 1000},\
	{0, 0, 0, -100, 0, 0, 0, 1, 2, 3}, 0xFFFFF0, 50, 0, (t_dot){0, M_PI_2, 0}\
	, tmp, NULL});
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
	add_light(&sdl->scene, (t_dot){300, 300, -1000}, 0.5);
	add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	add_light(&sdl->scene, (t_dot){300, 100, 550}, 0.4);
}
