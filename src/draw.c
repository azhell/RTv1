/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:55:59 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/16 15:56:01 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_draw(t_rtv1 *rt, int32_t x, int32_t y)
{
	t_buffer	buf_min;
	size_t		count;
	uint8_t		flag;
	t_rgb		color;

	count = 0;
	color = (t_rgb) {255, 255, 255};
	flag = 0;
	buf_min.distanse = 10000.0;
	while (count < rt->num_figure)
	{
		if (rt->buffer[count].distanse != -1.0)
		{
			if (buf_min.distanse > rt->buffer[count].distanse)
			{
				buf_min.distanse = rt->buffer[count].distanse;
				buf_min.color = rt->buffer[count].color;
				flag = 1;
			}
		}
		count++;
	}
	if (flag == 0)
		ft_put_pixel_rgb(rt, x, y, &color);
	else
		ft_put_pixel_rgb(rt, x, y, &buf_min.color);
}