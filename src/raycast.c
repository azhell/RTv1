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

float	ft_calc_figure(t_figure *figure, t_rtv1 *rt, t_ray *ray)
{
	t_all_fig	fig;
	float		result;

	if (figure->figure == sphere)
	{
		fig.sphere = (t_sphere*)figure->figure_data;
		result = ft_inter_sphere(fig.sphere->radius, fig.sphere->pos, rt, ray);
		fig.sphere = NULL;
		//printf("%f\n", result);
		return (result > 0);
	}
	return (0);
}

// void	ft_gen_ray(t_rtv1 *rt, t_ray *ray)
// {
// 	double	x;
// 	double	y;
// }

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;
	t_rgb		rgb;
	t_figure	*fig;
	double		u, v;
	float		res;

	ray.y = HT - 1;
	while (ray.y >= 0)
	{
		ray.x = 0;
		while (ray.x < WH)
		{
			fig = rt->figure;
			u = (float)ray.x / (float)WH;
			v = (float)ray.y / (float)HT;
			ray.color = (t_vector){u, v, 0.2};
			rgb.r = 34;
			rgb.g = 50;
			rgb.b = 39;
			ray.ray = rt->left_corner + rt->horizontal * u  + rt->vertical * v;
		//	printf("%f %f %f %f %f\n", ray.ray[X], ray.ray[Y], ray.ray[Z], rt->horizontal[X] * u, rt->vertical[Y] * v);
			while (fig)
			{
				res = ft_calc_figure(fig, rt, &ray);
				if (res)
				{
					rgb.r = 200;
					rgb.g = 0;
					rgb.b = 0;
					break ;
				}
				fig = fig->next;
			}
			ft_put_pixel_rgb(rt, ray.x, ray.y, rgb);
			ray.x++;
		}
		ray.y--;
	}
}