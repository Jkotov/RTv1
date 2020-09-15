#include "../include/rtv1.h"

int				color_intens(int color, float intens)
{
	return ((int)(((color & 0xFF000000) >> 24) * intens) << 24) +\
	((int)(((color & 0xFF0000) >> 16) * intens) << 16) +\
	((int)(((color & 0xFF00) >> 8) * intens) << 8) +\
	((int)(((color & 0xFF) * intens)));
}

int				color_sum(int c1, int c2)
{
	return ((int)(((c1 & 0xFF000000) >> 24) + ((c2 & 0xFF000000) >> 24)) << 24) +\
	((int)(((c1 & 0xFF0000) >> 16) + ((c2 & 0xFF0000) >> 16)) << 16) +\
	((int)(((c1 & 0xFF00) >> 8) + ((c2 & 0xFF00) >> 8)) << 8) +\
	((int)(c1 & 0xFF)  + (c2 & 0xFF));
}

int				ray_tracing(t_scene scene, t_dot direction_vector, t_dot start, int depth)
{
	int			cur_color;
	float		len;
	float		intens;
	t_sphere	*cur_sphere;
	t_dot		normal_vec;
	t_dot		dot;
	int			reflected_color;

	direction_vector = vector_normalize(direction_vector);
	cur_color = 0;
	len = INFINITY;
	cur_sphere = closest(start, direction_vector, scene, &len);
	if (len != INFINITY && scene.light)
	{
		dot = vector_sum(vector_mult_num(direction_vector, len), start);
		normal_vec = vector_normalize(vector_subtraction(dot, cur_sphere->center));
		intens = lighting(scene,\
		(t_compute_light_p){dot, cur_sphere->center,\
		cur_sphere->specular, vector_mult_num(direction_vector, -1),\
		normal_vec, cur_sphere});
		cur_color = color_intens(cur_sphere->color, intens);
		if (depth > 0)
		{
			reflected_color = ray_tracing(scene,\
			vector_reflection(direction_vector, normal_vec), dot, depth - 1);
			cur_color = color_sum(color_intens(cur_color,\
			(1 - cur_sphere->reflective)),
								  color_intens(reflected_color, cur_sphere->reflective));
			if (cur_color > 0xffffff)
				printf("IF U SEE THIS IN OUTPUT SOMETHING WENT WRONG");
		}
	}
	return (cur_color);
}


void			render(t_sdl *sdl)
{
	int		x;
	int		y;
	t_dot	direction_vector;

	SDL_LockTexture(sdl->fg, NULL, (void**)&sdl->buffer, &sdl->buffer_len);
	x = -1;
	y = -1;
	while (++x < sdl->width)
	{
		while (++y < sdl->height)
		{
			direction_vector = vector_subtraction((t_dot){x, y, 0},\
			sdl->scene.camera);
			sdl->buffer[y * sdl->width + x] = ray_tracing(sdl->scene,\
			direction_vector, (t_dot){(float)x, (float)y, 0}, 3);
		}
		y = -1;
	}
	SDL_UnlockTexture(sdl->fg);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->fg, NULL, NULL);
	SDL_RenderCopy(sdl->renderer, sdl->menu.img, NULL, &sdl->menu.menu_size);
	SDL_RenderPresent(sdl->renderer);
}