
#ifndef RTV1_H
# define RTV1_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "libft.h"

#define WIDTH 1280
#define HEIGHT 900

typedef	struct	s_vetrex
{
	double	x;
	double	y;
	double	z;
}				t_vertex;


typedef	struct	s_cam
{
	t_vertex	pos;

}				t_cam;

typedef	struct	s_rtv1
{
	SDL_Window	*win;
	SDL_Surface	*win_surf;
	SDL_Event	event;
}				t_rtv1;


void			ft_sdl_init(t_rtv1 *rt);
void			ft_sdlloop(t_rtv1 *rt);
void			ft_key(t_rtv1 *rt, int8_t *run);

#endif
