/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdlloop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:00:15 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 11:00:17 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

void	ft_sdlloop(t_rtv1 *rt)
{
	int8_t	run;

	run = 1;
	while (run)
	{
		ft_start_rt(rt);
		while (SDL_PollEvent(&rt->sdl.event))
		{
			ft_key(rt, &run);
		}
		SDL_UpdateWindowSurface(rt->sdl.win);
	}
}
