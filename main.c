/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:41:30 by epainter          #+#    #+#             */
/*   Updated: 2020/09/14 18:42:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		light_balancer(t_scene *scene)
{
	t_light	*tmp;
	float	max_light;

	max_light = 0;
	tmp = scene->light;
	while (tmp)
	{
		max_light += tmp->base_intensity;
		tmp = tmp->next;
	}
	tmp = scene->light;
	while (tmp)
	{
		tmp->intensity = tmp->base_intensity / max_light;
		tmp = tmp->next;
	}
}

void		add_light(t_scene *scene, t_dot center, float intensity)
{
	t_light *tmp;

	if (intensity > 0)
	{
		tmp = scene->light;
		if (!tmp)
		{
			tmp = (t_light *)malloc(sizeof(t_light));
			scene->light = tmp;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = (t_light*)malloc(sizeof(t_light));
			tmp = tmp->next;
		}
		tmp->center = center;
		tmp->base_intensity = intensity;
		tmp->next = NULL;
		light_balancer(scene);
	}
}

void		add_sphere(t_sphere **list, t_sphere sphere)
{
	t_sphere *tmp;

	if (!*list)
	{
		*list = (t_sphere *)malloc(sizeof(t_sphere));
		tmp = *list;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_sphere*)malloc(sizeof(t_sphere));
		tmp = tmp->next;
	}
	*tmp = sphere;
}

void		scene_init(t_sdl *sdl)
{
	sdl->scene.camera = (t_dot){(float)sdl->width\
	/ 2, (float)sdl->height / 2, -1000};
	sdl->scene.clipping_plane = 500;
	sdl->scene.sphere = NULL;
	sdl->scene.light = NULL;
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){300, 250, 150},\
	150, 0xFF00, 100, 0.3, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){400, 250, 150},\
	100, 0xFF, 75, 0.5, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){100, 250, 150},\
	125, 0xFF0000, 10, 1, NULL});
	add_sphere(&sdl->scene.sphere, (t_sphere){(t_dot){300, 5375, 150},\
	5000, 0xFFFF00, 10, 0.1, NULL});
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.1);
	add_light(&sdl->scene, (t_dot){0, 0, 0}, 0.5);
	add_light(&sdl->scene, (t_dot){1000, 40, 0}, 0.4);
	add_light(&sdl->scene, (t_dot){300, 100, 550}, 0.4);
}

t_sdl		sdl_init(void)
{
	t_sdl		sdl;

	sdl.width = 640;
	sdl.height = 480;
	scene_init(&sdl);
	sdl.buffer_len = sdl.width * sdl.height;
	sdl.window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED\
	, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (SDL_Init(0) != 0)
		sdl_error("SDL_Init Error: ");
	SDL_InitSubSystem(SDL_INIT_EVENTS);
	if (sdl.window == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1,\
	0);
	if (sdl.renderer == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		ft_putstr("IMG_Init");
		SDL_Quit();
	}
	return (sdl);
}

void		keyboard_events(t_sdl *sdl, char *quit, SDL_Event e)
{
	t_dot tmp;

	if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		*quit = 1;
	}
	if (e.key.keysym.sym == SDLK_SPACE)
		sdl->scene.sphere->center.z++;
	if (e.key.keysym.sym == SDLK_a)
	{
		while (e.button.type != SDL_MOUSEBUTTONDOWN)
			SDL_PollEvent(&e);
		tmp = (t_dot){e.button.x, e.button.y, 300};
		e.button.type = 0;
		while (e.button.type != SDL_MOUSEBUTTONDOWN)
			SDL_PollEvent(&e);
		add_sphere(&sdl->scene.sphere, (t_sphere){tmp,\
		abs_vector(vector_subtraction((t_dot){e.button.x, e.button.y, 300},\
		tmp)), 0xFF00, 100, 0.3, NULL});
	}
}

int			quadratic_equation(t_dot coeffs, float *x1, float *x2)
{
	float	d;

	if (coeffs.x == 0)
		return (0);
	d = coeffs.y * coeffs.y - 4 * coeffs.x * coeffs.z;
	if (d < 0)
		return (0);
	if (d == 0)
	{
		*x1 = -coeffs.y * 0.5 / coeffs.x;
		*x2 = *x1;
		return (1);
	}
	d = sqrtf(d);
	*x1 = (-coeffs.y - d) * 0.5 / coeffs.x;
	*x2 = (-coeffs.y + d) * 0.5 / coeffs.x;
	return (2);
}

float		q_rsqrt(float number)
{
	int			n;
	float		res;
	const float x2 = number * 0.5F;
	const float threehalfs = 1.5F;

	n = 0x5f3759df - (*(int*)&number >> 1);
	res = (*(float *)&n);
	res *= (threehalfs - (x2 * res * res));
	res *= (threehalfs - (x2 * res * res));
	return (res);
}

/*
** if something went wrong try
** scalar_mult(direction_vec, direction_vec)
** instead 1 as A in quadratic_equation
*/

float			distance_to_sphere(t_dot direction_vec,\
t_dot vec_to_center, float radius)
{
	float		solutions[2];

	if (!quadratic_equation((t_dot){1,\
	2 * scalar_mult(direction_vec, vec_to_center),\
	scalar_mult(vec_to_center, vec_to_center) - radius\
	* radius}, &solutions[0], &solutions[1]))
		return (NAN);
	if (solutions[0] > solutions[1])
		solutions[0] = solutions[1];
	return (solutions[0]);
}

t_sphere		*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len)
{
	float		cur_len;
	t_dot		vector_to_center;
	t_sphere	*cur_sphere;
	t_sphere	*res;

	res = NULL;
	cur_sphere = scene.sphere;
	while (cur_sphere)
	{
		vector_to_center = vector_subtraction(start, cur_sphere->center);
		if ((cur_len = distance_to_sphere(direction_vector,\
		vector_to_center, cur_sphere->radius)) != NAN)
		{
			if (*len > cur_len && cur_len > 0)
			{
				res = cur_sphere;
				*len = cur_len;
			}
		}
		cur_sphere = cur_sphere->next;
	}
	return (res);
}

float			specular(t_compute_light_p p,\
t_dot light_vector, float intensity)
{
	t_dot	specular_vector;
	float	tmp;

	if (p.specular <= 0)
		return (0);
	specular_vector =\
	vector_subtraction(vector_mult_num(vector_mult_num(p.normal_vec,\
	2), scalar_mult(p.normal_vec, light_vector)), light_vector);
	if (scalar_mult(specular_vector, p.direction_vec) < 0)
		return (0);
	tmp = powf(scalar_mult(specular_vector, p.direction_vec)\
	* revers_abs_vec(specular_vector), p.specular) * intensity;
	return (tmp);
}

float			lighting(t_scene scene, t_compute_light_p p)
{
	float	res;
	t_light	*cur_light;
	t_dot	light_vector;
	float	tmp;

	p.normal_vec = vector_normalize(vector_subtraction(p.dot, p.center));
	res = scene.light->intensity;
	cur_light = scene.light->next;
	while (cur_light)
	{
		light_vector = vector_subtraction(cur_light->center, p.dot);
		tmp = INFINITY;
		if (!(closest(p.dot, (vector_normalize(light_vector)),\
		scene, &tmp)))
		{
			tmp = scalar_mult(p.normal_vec, light_vector)\
			* revers_abs_vec(light_vector) * cur_light->intensity;
			res = tmp > 0 ? res + tmp : res;
			res += specular(p, light_vector, cur_light->intensity);
		}
		cur_light = cur_light->next;
	}
	res = res > 1 ? 1 : res;
	return (res);
}

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

void			mouse_events(t_sdl *sdl, SDL_Event e)
{
	t_sphere sphere;

	sphere.center = (t_dot){0, 0, 0};
	sphere.specular = 0;
	sphere.radius = 0;
	sphere.color = 0;
	if (e.button.y < 100)
	{
		if (e.button.x > 100 && e.button.x < 200)
		{
			SDL_RenderCopy(sdl->renderer, sdl->menu.add_menu, NULL, &sdl->menu.add_menu_size);
			SDL_RenderPresent(sdl->renderer);
			while (e.type != SDL_MOUSEBUTTONDOWN || (e.button.x > 100))
			{
				SDL_PollEvent(&e);
			}
		}
	}
}

void			loop(t_sdl *sdl)
{
	SDL_Event	e;
	char		quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_KEYDOWN)
				keyboard_events(sdl, &quit, e);
			if (e.type == SDL_MOUSEBUTTONDOWN)
				mouse_events(sdl, e);
		}
		render(sdl);
	}
}

void			init_menu(t_sdl *sdl)
{
	sdl->menu.menu_size = (SDL_Rect){0, 0, sdl->width, 30};
	sdl->menu.img = create_texture("menu.png", sdl);
	sdl->menu.add_menu_size = (SDL_Rect){450, 100, 150, 350};
	sdl->menu.add_menu = create_texture("add_coords.png", sdl);
}

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
