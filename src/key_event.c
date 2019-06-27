
#include "rtv1.h"

void	ft_exit(t_rtv1 *rt, int8_t *run)
{
	if (rt->event.type == SDL_QUIT ||
		(SDL_SCANCODE_ESCAPE == rt->event.key.keysym.scancode))
		*run = 0;
}

void	ft_key(t_rtv1 *rt, int8_t *run)
{

	ft_exit(rt, run);
}