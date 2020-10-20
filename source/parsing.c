/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:11:05 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 07:11:40 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "ini_parser.h"

void			parse_light(t_sdl *sdl, t_block *tmp)
{
	add_light(&sdl->scene,\
	(t_dot){(float)ft_atoi(find_value("SHIFTX", tmp)),\
	(float)ft_atoi(find_value("SHIFTY", tmp)),\
	(float)ft_atoi(find_value("SHIFTZ", tmp))},\
	(float)ft_atoi(find_value("INTENSITY", tmp)) / 100);
}

void			parse_surface(t_sdl *sdl, t_block *tmp)
{
	t_surface_cache cache;

	ft_memset(&cache, 0, sizeof(cache));
	add_shape(&sdl->scene.shape,\
		(t_surface){(t_dot){(float)ft_atoi(find_value("SHIFTX", tmp)),\
		(float)ft_atoi(find_value("SHIFTY", tmp)),\
		(float)ft_atoi(find_value("SHIFTZ", tmp))},\
		(t_surface_coeffs){(float)ft_atoi(find_value("A", tmp)),\
		(float)ft_atoi(find_value("B", tmp)),\
		(float)ft_atoi(find_value("C", tmp)),\
		(float)ft_atoi(find_value("D", tmp)),\
		(float)ft_atoi(find_value("2F", tmp)),\
		(float)ft_atoi(find_value("2G", tmp)),\
		(float)ft_atoi(find_value("2H", tmp)),\
		(float)ft_atoi(find_value("2P", tmp)),\
		(float)ft_atoi(find_value("2Q", tmp)),\
		(float)ft_atoi(find_value("2R", tmp))},\
		ft_atoi_base(find_value("COLOR", tmp), 16),\
	ft_atoi(find_value("SPECULAR", tmp)),\
	(float)ft_atoi(find_value("REFLECTIVE", tmp)) / 100,\
	(t_dot){(float)ft_atoi(find_value("ANGLEX", tmp)) * M_PI / 180,\
	(float)ft_atoi(find_value("ANGLEY", tmp)) * M_PI / 180,\
	(float)ft_atoi(find_value("ANGLEZ", tmp)) * M_PI / 180}, cache,\
	0, NULL
	});
}

void			parse_camera(t_sdl *sdl, t_block *tmp)
{
	sdl->scene.camera.camera.x = (float)ft_atoi(find_value("SHIFTX", tmp));
	sdl->scene.camera.camera.y = (float)ft_atoi(find_value("SHIFTY", tmp));
	sdl->scene.camera.camera.z = (float)ft_atoi(find_value("SHIFTZ", tmp));
	sdl->scene.camera.angle.x = (float)ft_atoi(find_value("ANGLEX",\
	tmp)) * M_PI / 180;
	sdl->scene.camera.angle.y = (float)ft_atoi(find_value("ANGLEY",\
	tmp)) * M_PI / 180;
	sdl->scene.camera.angle.z = (float)ft_atoi(find_value("ANGLEZ",\
	tmp)) * M_PI / 180;
	camera_move(sdl);
}

void			parsing(t_sdl *sdl, char *scene_file)
{
	t_block	*root;
	t_block	*tmp;

	ini_parser(scene_file, &root);
	tmp = root;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "surface") == 0)
			parse_surface(sdl, tmp);
		if (ft_strcmp(tmp->name, "light") == 0)
			parse_light(sdl, tmp);
		if (ft_strcmp(tmp->name, "camera") == 0)
			parse_camera(sdl, tmp);
		tmp = tmp->next;
	}
	cleanup_ini(root);
}
