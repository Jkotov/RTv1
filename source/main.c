/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:41:30 by epainter          #+#    #+#             */
/*   Updated: 2020/09/30 17:43:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int				main(int argc, char **argv)
{
	t_sdl		sdl;

	if (argc > 2)
		sdl_error("too many args");
	sdl = sdl_init();
	if (argc == 2)
		parsing(&sdl, argv[1]);
	init_menu(&sdl);
	sdl.fg = SDL_CreateTexture(sdl.renderer,\
	SDL_PIXELFORMAT_ARGB8888,\
	SDL_TEXTUREACCESS_STREAMING, sdl.width, sdl.height);
	SDL_RenderClear(sdl.renderer);
	loop(&sdl);
	cleanup(&sdl);
	return (0);
}
