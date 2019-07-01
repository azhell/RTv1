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

	ray.y = 0;
	while (ray.y < HEIGHT)
	{
		ray.x = 0;
		while (ray.x < WIDTH)
		{
			//suka blytb
			ray.x++;
		}
		ray.y++;
	}
}