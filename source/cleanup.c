/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:36:33 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 10:16:22 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		clean_light(t_light *light)
{
	if (!light)
		return ;
	if (light->next)
		clean_light(light->next);
	free(light);
	light = NULL;
}

void		clean_sphere(t_surface *sphere)
{
	if (!sphere)
		return ;
	if (sphere->next)
		clean_sphere(sphere->next);
	free(sphere);
	sphere = NULL;
}

void		clean_scene(t_scene *scene)
{
	clean_sphere(scene->shape);
	scene->shape = NULL;
	clean_light(scene->light);
	scene->light = NULL;
}

void		clean_menu(t_menu *m)
{
	SDL_DestroyTexture(m->img);
}

void		cleanup(t_sdl *sdl)
{
	clean_scene(&sdl->scene);
	free(sdl->scene.camera.dir_vecs);
	clean_menu(&sdl->menu);
	SDL_DestroyTexture(sdl->fg);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_Quit();
}
