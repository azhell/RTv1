/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:00:08 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 11:00:09 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_gen_ray(t_rtv1 *rt, t_ray *ray)
{
	double	x;
	double	y;

	x = (WIDTH - ray->x * 2.0) / HEIGHT;
	y = (HEIGHT - ray->y * 2.0) / WIDTH;
	ray->vec = ft_vec_sub(rt->camera.direct, rt->camera.pos);
	ft_vec_normailize(&ray->vec);
}

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;
	t_rgb		rgb;

	ray.y = 0;
	while (ray.y < HEIGHT)
	{
		ray.x = 0;
		while (ray.x < WIDTH)
		{
			float r	= (float)ray.x / (float)WIDTH;
			float g	= (float)ray.y / (float)HEIGHT;
			float b = 0.2;
			rgb.r = (int)(r * 255.9);
			rgb.g = (int)(g * 255.9);
			rgb.b = (int)(b * 255.9);
			ft_put_pixel_rgb(rt, ray.x, ray.y, rgb);
			ray.x++;
		}
		ray.y++;
	}
}