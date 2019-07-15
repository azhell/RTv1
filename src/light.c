/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:08:44 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/10 14:08:47 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_light(t_light *light, t_ray *ray, t_calc_light *calc)
{
	double	angle_lht;
	double	angle_cam;
	double	color_i;

	color_i = 0.0;
	color_i += light->str;
	angle_lht = ft_vec_scalar(ft_vec_normalize(light->pos - calc->point),
		calc->normal);
	angle_cam = ft_vec_scalar(calc->ray_vec, calc->normal);

	// fix color after
	if (angle_lht > 0.0)
	{
		color_i -= 1.0 - angle_lht;
		//printf("%f | ", color_i);
		if (color_i > 1.0)
			color_i = 1.0;
		if (color_i < 0.0)
			color_i = 0;
		ray->color.r = 255 - ray->color.r * color_i;
		ray->color.g = 255 - ray->color.g * color_i;
		ray->color.b = 255 - ray->color.b * color_i;
		// if (fabs(angle_lht - angle_cam) <= 0.1)
		// {
		// 	KEK;
		// ray->color.r = 0;
		// ray->color.g = 255;
		// ray->color.b = 0;
		// }
	}
	else
		ray->color = (t_rgb) {255, 255, 255};
	
}