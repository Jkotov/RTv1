/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:36:33 by epainter          #+#    #+#             */
/*   Updated: 2020/09/26 02:49:57 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		clean_light(t_light *light)
{
	if (light->next)
		clean_light(light->next);
	free(light);
}

void		clean_sphere(t_surface *sphere)
{
	if (sphere->next)
		clean_sphere(sphere->next);
	free(sphere);
}

void		clean_scene(t_scene *scene)
{
	clean_sphere(scene->conic);
	clean_light(scene->light);
	free(scene->camera.dir_vecs);
}

void		clean_menu(t_menu *m)
{
	SDL_DestroyTexture(m->add_menu);
	SDL_DestroyTexture(m->img);
}

void		cleanup(t_sdl *sdl)
{
	clean_scene(&sdl->scene);
	//clean_menu(&sdl->menu);
	SDL_DestroyTexture(sdl->fg);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Quit();
}
