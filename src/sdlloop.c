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

void	ft_sdlloop(t_rtv1 *rt, t_thread *th)
{
	int8_t	run;
	int8_t	update;

	run = 1;
	update = 1;
	while (run)
	{
		while (SDL_PollEvent(&rt->sdl.event))
			ft_key(rt, &run);
		if (update == 1)
		{
			ft_start_rt_thread(rt, th);
			update = 0;
		}
		SDL_UpdateWindowSurface(rt->sdl.win);
	}
}
