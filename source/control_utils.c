

#include "../include/rtv1.h"

# define PURPLE 0x7a3bc2
# define MINT 0x46ba89
# define ORANGE 0xe76726
# define RED 0xb71c1c
# define WHITE 0xFFFFFF

t_dot			get_position(int x_coord)
{
	t_dot position;

	if (x_coord > 319 && x_coord < 367)
		position = (t_dot){500, 100, 300};
	else if (x_coord > 372 && x_coord < 419)
		position = (t_dot){600, 200, 200};
	else if (x_coord > 424 && x_coord < 473)
		position = (t_dot){500, 300, 300};
	else if (x_coord > 478 && x_coord < 526)
		position = (t_dot){600, 400, 400};
	return (position);
}

float 			get_radius(int x_coord)
{
	float  radius;

	if (x_coord > 108 && x_coord < 157)
		radius = 50;
	else if (x_coord > 157 && x_coord < 210)
		radius = 100;
	else if (x_coord > 210 && x_coord < 260)
		radius = 150;
	else if (x_coord > 260 && x_coord < 316)
		radius = 200;
	return (radius);
}

int				get_color(int x_coord)
{
	int 	color;

	if (x_coord > 108 && x_coord < 157)
		 color = RED;
		else if (x_coord > 157 && x_coord < 210)
			color = ORANGE;
		else if (x_coord > 210 && x_coord < 260)
			color = MINT;
		else if (x_coord > 260 && x_coord < 316)
			color = PURPLE;
	return (color);
}

void			button_create_sphere(t_sdl *sdl, t_gui_cache *gui_cache)
{
	add_sphere(&sdl->scene.sphere, (t_sphere){gui_cache->position, \
	gui_cache->radius, gui_cache->color, 100, 0.3, \
	NULL, NULL});

}

void			gui_buttons(t_gui_cache *gui_cache, SDL_Event e)
{
	if (gui_cache->color != RED && gui_cache->color != ORANGE \
		&& gui_cache->color != MINT && gui_cache->color != PURPLE && \
		gui_cache->radius < 50.0000 && gui_cache->position.x < 100.0000)
	{
		gui_cache->radius = 80;
		gui_cache->color = WHITE;
		gui_cache->position = (t_dot){400, 200, 300};
	}
	if (e.button.y > 80 && e.button.y < 105)
	{
//		colors
		gui_cache->color = get_color(e.button.x);
	}
	else if (e.button.y > 70 && e.button.y < 85)
	{
//		radius
		gui_cache->radius = get_radius(e.button.x);
	}
	if (e.button.y > 90 && e.button.y < 102)
	{
//		position
		gui_cache->position = get_position(e.button.x);
	}
}

void			mouse_events(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	gui_buttons(gui_cache, e);
	printf("color = %d\n radius = %f\n position = {%f, %f, %f}\n", gui_cache->color, gui_cache->radius, \
	gui_cache->position.x, gui_cache->position.y, gui_cache->position.z);
	if (e.button.y > 50 && e.button.y < 65)
	{
		if ((e.button.x > 0 && e.button.x < 50))
			button_create_sphere(sdl, gui_cache);
	}
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
		tmp)), 0xFF00, 100, 0.3, NULL, NULL});
	}
}