/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:01:56 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/03 17:01:58 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_init(t_rtv1 *rt)
{
	t_buffer	*buffer;

	rt->size = sizeof(t_buffer) * rt->num_figure;
	buffer = ft_memalloc(rt->size);
	ft_bzero(buffer, rt->size);
	rt->buffer = buffer;
}