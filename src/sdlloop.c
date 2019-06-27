
#include "rtv1.h"

void	ft_sdlloop(t_rtv1 *rt)
{
	int8_t	run;

	run = 1;
	while (run)
	{
		SDL_FillRect(rt->win_surf, NULL, 0x00FFFF);
		while (SDL_PollEvent(&rt->event))
		{
			ft_key(rt, &run);
		}
		SDL_UpdateWindowSurface(rt->win);
	}
}