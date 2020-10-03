/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:41:30 by epainter          #+#    #+#             */
/*   Updated: 2020/10/03 00:14:24 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				main(void)
{
	t_sdl		sdl;
	t_cl		cl;

	sdl = sdl_init();
	//init_menu(&sdl);
	sdl.fg = SDL_CreateTexture(sdl.renderer,\
	SDL_PIXELFORMAT_ARGB8888,\
	SDL_TEXTUREACCESS_STREAMING, sdl.width, sdl.height);
	SDL_RenderClear(sdl.renderer);
	cl = cl_init(&sdl);
	//loop(&sdl);
	cleanup(&sdl, &cl);
	return (0);
}
