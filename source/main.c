/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:41:30 by epainter          #+#    #+#             */
/*   Updated: 2020/09/16 15:18:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int				main(void)
{
	t_sdl		sdl;

	sdl = sdl_init();
	init_menu(&sdl);
	sdl.fg = SDL_CreateTexture(sdl.renderer,\
	SDL_PIXELFORMAT_ARGB8888,\
	SDL_TEXTUREACCESS_STREAMING, 640, 480);
	SDL_RenderClear(sdl.renderer);
	loop(&sdl);
	cleanup(&sdl);
	return (0);
}
