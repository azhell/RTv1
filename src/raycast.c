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

void	ft_get_angle_ver(t_rtv1 *rt, t_ray *ray)
{
	ray->angle.angle_ver = -atan((HALFHEIGHT - ray->y) / DIST);
}

void	ft_get_angle_hor(t_rtv1 *rt, t_ray *ray)
{
	ray->angle.angle_hor = -atan((HALFWIDTH - ray->x) / DIST);
}

void	ft_set_end_ray(t_rtv1 *rt, t_ray *ray)
{

}

void	ft_cast_ray(t_rtv1 *rt)
{

}

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;

	ray.y = 0;
	while (ray.y < 1)
	{
		ray.x = 0;
		ft_get_angle_ver(rt, &ray);
		while (ray.x < WIDTH)
		{
			ft_get_angle_hor(rt, &ray);
			ft_set_end_ray(rt, &ray);

			ray.x++;
		}
		ray.y++;
	}
}