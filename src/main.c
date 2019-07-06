/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:59:58 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 10:59:59 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rtv1 *ft_mem_main(void)
{
	t_rtv1 *rt;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		ft_print_error(BAD_ALLOC);
	return (rt);
}

int main(int ac, char **av)
{
	t_rtv1 *rt;

	if (ac != 2)
		ft_print_error(BAD_USAGE);
	rt = ft_mem_main();
	ft_read(av[1], rt);
	ft_init(rt);
	ft_start_rt(rt);
	// ft_sdl_init(rt);
	// ft_sdlloop(rt);
	// SDL_Quit();
	//system("leaks RTv1");
	return (0);
}
