

#include "../include/rtv1.h"

void			mouse_events(t_sdl *sdl, SDL_Event e)
{
	t_sphere sphere;

	sphere.center = (t_dot){0, 0, 0};
	sphere.specular = 0;
	sphere.radius = 0;
	sphere.color = 0;
	if (e.button.y < 40)
	{
		if (e.button.x < 90)
		{
			//			add sphere
					printf("1\n");
			//			SDL_RenderCopy(sdl->renderer, sdl->menu.add_menu, NULL, &sdl->menu.add_menu_size);
//			SDL_RenderPresent(sdl->renderer);
//			while (e.type != SDL_MOUSEBUTTONDOWN || (e.button.x > 100))
//			{
//				SDL_PollEvent(&e);
//
//			}
		}
		if (e.button.x > 90 && e.button.x < 185)
		{
			//			add cone
			printf("2\n");
		}
		if (e.button.x > 185 && e.button.x < 280)
		{
			//			add plane
			printf("3\n");
		}
		if (e.button.x > 280 && e.button.x < 390)
		{
			//			add cylinder
			printf("4\n");
		}
		if (e.button.x > 390 && e.button.x < 480)
		{
//			add light
			printf("5\n");
		}
		if (e.button.x > 480 && e.button.x < 540)
		{
//			reset
			printf("6\n");
		}
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
		tmp)), 0xFF00, 100, 0.3, NULL});
	}
}