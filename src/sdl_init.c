
#include "rtv1.h"

void	ft_sdl_init(t_rtv1 *rt)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	rt->win = SDL_CreateWindow(
		"Doom Nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	rt->win_surf = SDL_GetWindowSurface(rt->win);
}