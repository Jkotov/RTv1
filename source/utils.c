#include "../include/rtv1.h"

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