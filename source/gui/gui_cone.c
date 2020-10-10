#include "../../include/rtv1.h"

void			button_create_cone(t_sdl *sdl, t_gui_cache *gui_cache)
{
	t_surface_cache tmp;

	ft_memset(&tmp, 0, sizeof(tmp));
	add_sphere(&sdl->scene.conic, (t_surface){gui_cache->position, {1, 2,\
	-1, 0, 0, 0, 0, 0, 0, 0}, gui_cache->color, 10, 0.3, (t_dot){0, M_PI_2, 0},\
	tmp, NULL});

}

void 			gui_cone(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache)
{
	if ((e.button.x > 100 && e.button.x < 150))
		button_create_cone(sdl, gui_cache);
	else if (e.button.x > 150 && e.button.x < 210)
	{
		printf("sdl->scene.conic->c.a = %f\n",sdl->scene.conic->c.a);
		printf("sdl->scene.conic->c.b = %f\n",sdl->scene.conic->c.b);
		printf("sdl->scene.conic->c.c = %f\n",sdl->scene.conic->c.c);
		printf("sdl->scene.conic->angle.y = %f\n.", sdl->scene.conic->angle.x);
		if (count_objs(sdl->scene.conic) != 3)
			if(sdl->scene.conic->angle.y == M_PI_2)
			{
				printf("sdl->scene.conic->angle.y = %f\n.", sdl->scene.conic->angle.y);
				del_objs(&sdl->scene.conic);
			}
	}
}