/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:59:49 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 10:59:50 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

void	ft_sdl_init(t_rtv1 *rt)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	rt->sdl.win = SDL_CreateWindow(
		"RTv1",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	rt->sdl.win_surf = SDL_GetWindowSurface(rt->sdl.win);
	if (rt->sdl.win_surf == NULL)
		exit(-1);
}
