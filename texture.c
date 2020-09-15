/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:36:56 by epainter          #+#    #+#             */
/*   Updated: 2020/08/21 14:15:04 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

SDL_Texture	*create_texture(char *file_name, t_sdl *sdl)
{
	SDL_Texture *tex;

	tex = IMG_LoadTexture(sdl->renderer, file_name);
	if (tex == NULL)
		sdl_error("IMG Load Error: ");
	return (tex);
}
