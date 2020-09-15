#include "../include/rtv1.h"

int				color_intens(int color, float intens)
{
	return ((int)(((color & 0xFF000000) >> 24) * intens) << 24) +\
	((int)(((color & 0xFF0000) >> 16) * intens) << 16) +\
	((int)(((color & 0xFF00) >> 8) * intens) << 8) +\
	((int)(((color & 0xFF) * intens)));
}

int				ray_tracing(t_scene scene, t_dot direction_vector, t_dot start)
{
	int			cur_color;
	float		len;
	float		intens;
	t_sphere	*cur_sphere;

	direction_vector = vector_normalize(direction_vector);
	cur_color = 0;
	len = INFINITY;
	cur_sphere = closest(start, direction_vector, scene, &len);
	if (len != INFINITY && scene.light)
	{
		intens = lighting(scene,\
		(t_compute_light_p){vector_sum(vector_mult_num(direction_vector,\
		len), start), cur_sphere->center,\
		cur_sphere->specular, vector_mult_num(direction_vector, -1),\
		{0, 0, 0}, cur_sphere});
		cur_color = color_intens(cur_sphere->color, intens);
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
			direction_vector, (t_dot){(float)x, (float)y, 0});
		}
		y = -1;
	}
	SDL_UnlockTexture(sdl->fg);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->fg, NULL, NULL);
	SDL_RenderCopy(sdl->renderer, sdl->menu.img, NULL, &sdl->menu.menu_size);
	SDL_RenderPresent(sdl->renderer);
}