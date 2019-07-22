/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:59:37 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 10:59:39 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_exit(t_rtv1 *rt, int8_t *run)
{
	if (rt->sdl.event.type == SDL_QUIT ||
		(SDL_SCANCODE_ESCAPE == rt->sdl.event.key.keysym.scancode))
		*run = 0;
}


void	ft_move_cam(t_rtv1 *rt)
{
	if (rt->sdl.event.type == SDL_KEYUP && rt->sdl.event.key.keysym.sym == SDLK_UP)
	{
		rt->camera.pos[Z] += 0.5;
		rt->camera.direct[Z] += 0.5;
	}
	if (rt->sdl.event.type == SDL_KEYUP && rt->sdl.event.key.keysym.sym == SDLK_DOWN)
	{
		rt->camera.pos[Z] -= 0.5;
		rt->camera.direct[Z] -= 0.5;
	}
	if (rt->sdl.event.type == SDL_KEYUP && rt->sdl.event.key.keysym.sym == SDLK_LEFT)
	{
		rt->camera.pos[Y] -= 0.5;
		rt->camera.direct[Y] -= 0.5;
	}
	if (rt->sdl.event.type == SDL_KEYUP && rt->sdl.event.key.keysym.sym == SDLK_RIGHT)
	{
		rt->camera.pos[Y] += 0.5;
		rt->camera.direct[Y] += 0.5;
	}
}

void	ft_key(t_rtv1 *rt, int8_t *run)
{

	ft_exit(rt, run);
	ft_move_cam(rt);
}
