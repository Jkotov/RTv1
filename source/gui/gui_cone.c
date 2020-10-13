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
}