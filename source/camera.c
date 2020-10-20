/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:28:04 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 18:33:56 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			directions_vec_compute(t_sdl *sdl, t_dot **dir_vecs)
{
	t_camera	tmp;
	int			x;
	int			y;
	t_dot		dot;

	tmp = sdl->scene.camera;
	if ((*dir_vecs = *dir_vecs ? *dir_vecs : (t_dot*)malloc(sizeof(t_dot) *\
	sdl->width * sdl->height)) == NULL)
		sdl_error("Alloc error");
	x = -1;
	y = -1;
	while (++x < sdl->width)
	{
		while (++y < sdl->height)
		{
			dot = vector_sum(tmp.screen_center, vector_mult_num(tmp.x_vec,\
			sdl->width / 2 - x));
			dot = vector_sum(dot, vector_mult_num(tmp.y_vec,\
			sdl->height / 2 - y));
			(*dir_vecs)[y * sdl->width + x] =
					vector_normalize(vector_sub(dot, tmp.camera));
		}
		y = -1;
	}
}

void			camera_move(t_sdl *sdl)
{
	t_camera	tmp;

	tmp = sdl->scene.camera;
	tmp.center_vec = rotate_vector((t_dot){0, 0, 1}, tmp.angle);
	tmp.screen_center = vector_sum(vector_mult_num(tmp.center_vec,\
	1000), tmp.camera);
	tmp.x_vec = rotate_vector((t_dot){1, 0, 0}, tmp.angle);
	tmp.y_vec = rotate_vector((t_dot){0, 1, 0}, tmp.angle);
	sdl->scene.camera = tmp;
	directions_vec_compute(sdl, &sdl->scene.camera.dir_vecs);
}
