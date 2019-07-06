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

double	ft_check_figure(t_rtv1 *rt, t_ray *ray, t_figure *figure)
{
	double		result;
	t_all_fig	*fig;

	result = 0.f;
	fig = ft_memalloc(sizeof(t_all_fig));
	if (figure->figure == sphere)
	{
		fig->sphere = figure->figure_data;
		result = ft_inter_sphere(fig->sphere->pos, fig->sphere->radius, ray, rt);
		free(fig);
	}
	else if (figure->figure == cylinder)
	{

	}
	else if (figure->figure == cone)
	{

	}
	else if (figure->figure == plane)
	{

	}
	return (result);
}

double	ft_start_figure(t_rtv1 *rt, t_ray *ray)
{
	t_figure	*fig;
	double		res;

	fig = rt->figure;
	res = -1;
	while (fig)
	{
		res = ft_check_figure(rt, ray, fig);
		fig = fig->next;
	}
	return (res);
}

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;
	t_rgb		rgb;
	double		res;

	ray.y = 0;
	rgb.r = 50;
	rgb.g = 50;
	rgb.r = 50;
	while (ray.y < HT)
	{
		ray.x = 0;
		while (ray.x < WH)
		{
			ray.u	= (float)ray.x / (float)WH;
			ray.v	= (float)ray.y / (float)HT;
			
			ray.vec = rt->data.left_corn + ft_vec_add_scale(rt->data.horizontal, ray.u)
			+ ft_vec_add_scale(rt->data.vertical, ray.v);
			res = ft_start_figure(rt, &ray);
			if (res >= 0)
			{
				rgb.r = 200;
				rgb.g = 0;
				rgb.b = 0;
			}
			else
			{
				rgb.r = 50;
				rgb.g = 50;
				rgb.b = 50;
			}
				
			//printf("%f %f %f %d %d\n", ray.vec[X], ray.vec[Y], ray.vec[Z], ray.y, ray.x);
			ft_put_pixel_rgb(rt, ray.x, ray.y, &rgb);
			ray.x++;
		}
		ray.y++;
	}
}