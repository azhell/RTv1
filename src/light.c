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

void	ft_light(t_light *light, t_ray *ray, t_calc_light *calc, t_rtv1 *rt)
{
	double	angle_lht;
	double	angle_cam;
	double	color_i;
	double	len;
	t_vector	vec_light;
	t_figure	*tmp;

	color_i = light->intense;
	tmp = rt->figure;
	vec_light = ft_vec_normalize(calc->point - light->pos);
	angle_lht = ft_vec_scalar(vec_light, -calc->normal);
	angle_cam = ft_vec_scalar(ray->ray, calc->normal);
//	printf("%f %f || ", angle_lht, angle_cam);
	if (calc->flag_plane == 1)
		angle_lht = fabs(angle_lht);
	len = ft_vec_len(calc->point, light->pos);
	// fix color after
	if (angle_lht > 0.0)
	{
		color_i -= 1.0 - angle_lht;
		color_i -= DAMPING * len;
		//printf("%f | ", color_i);
		if (color_i > 1.0)
			color_i = 1.0;
		if (color_i < 0.0)
			color_i = 0;
		ray->color.r = 255 - ray->color.r * color_i;
		ray->color.g = 255 - ray->color.g * color_i;
		ray->color.b = 255 - ray->color.b * color_i;
		// if ((fabs(angle_cam) - fabs(angle_lht)) < 0.01)
		// {
		// 	ray->color.r = 14;
		// 	ray->color.g = 23;
		// 	ray->color.b = 24;
		// }
	}
	else
		ray->color = (t_rgb) {255, 255, 255};
}