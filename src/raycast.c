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

<<<<<<< HEAD
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
=======
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
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
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
<<<<<<< HEAD
	t_figure	*fig;
	double		u, v;
	float		res;

	ray.y = HT - 1;
	while (ray.y >= 0)
=======
	double		res;

	ray.y = 0;
	rgb.r = 50;
	rgb.g = 50;
	rgb.r = 50;
	while (ray.y < HT)
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
	{
		ray.x = 0;
		while (ray.x < WH)
		{
<<<<<<< HEAD
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
=======
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
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
			ray.x++;
		}
		ray.y--;
	}
}