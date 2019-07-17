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
	t_all_fig		fig;
	t_calc_light	*result;

	if (figure->figure == sphere)
	{
		fig.sphere = (t_sphere*)figure->figure_data;
		ray->color = fig.sphere->color;
		result = ft_inter_sphere(fig.sphere, rt, ray);
		fig.sphere = NULL;
		if (result != NULL)
		{
			ft_light(rt->light, ray, result, rt);
			return (1);
		}
	}
	if (figure->figure == plane)
	{
		fig.plane = (t_plane*)figure->figure_data;
		ray->color = fig.plane->color;
		result = ft_inter_plane(rt, ray, fig.plane);
		fig.plane = NULL;
		if (result != NULL)
		{
			ft_light(rt->light, ray, result, rt);
			return (1);
		}

	}
	if (figure->figure == cylinder)
	{
		fig.cylinder = (t_cylinder*)figure->figure_data;
		ray->color = fig.cylinder->color;
		result = ft_inter_cylinder(rt, ray, fig.cylinder);
		fig.cylinder = NULL;
		if (result != NULL)
		{
			ft_light(rt->light, ray, result, rt);
			return (1);
		}
	}
	if (figure->figure == cone)
	{
		fig.cone = (t_cone*)figure->figure_data;
		ray->color = fig.cone->color;
		result = ft_inter_cone(rt, ray, fig.cone);
		fig.cone = NULL;
		if (result != NULL)
		{
			ft_light(rt->light, ray, result, rt);
			return (1);
		}
	}
	return (0);
}

void	ft_gen_ray(t_rtv1 *rt, t_ray *ray)
{
	double	u, v;
	t_vector	tab;
	t_vector	corn;
	t_vector	dir;

	v = (double)(WH - ray->x * 2.0) / (double)WH;
	u = (double)(HT - ray->y * 2.0) / (double)WH;
	corn = (t_vector) {0.0, 1.0, 0.0};
	rt->camera.vector = ft_vec_sub(rt->camera.direct, rt->camera.pos);
	rt->camera.vector = ft_vec_normalize(rt->camera.vector);
	tab = ft_vec_cross(rt->camera.vector, corn);
	tab = ft_vec_normalize(tab);
	dir = ft_vec_cross(rt->camera.vector, tab);
	ray->ray[X] = u * tab[X] + v * dir[X] + 2.0 * rt->camera.vector[X];
	ray->ray[Y] = u * tab[Y] + v * dir[Y] + 2.0 * rt->camera.vector[Y];
	ray->ray[Z] = u * tab[Z] + v * dir[Z] + 2.0 * rt->camera.vector[Z];
	ray->ray = ft_vec_normalize(ray->ray);
}

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;
	t_figure	*fig;
	float		res;
	int32_t		count;

	ray.y = 0;
	while (ray.y < HT)
	{
		ray.x = 0;
		while (ray.x < WH)
		{
			fig = rt->figure;
			ft_gen_ray(rt, &ray);
			count = 0;
			ft_bzero(rt->buffer, rt->size);
			while (fig)
			{
				res = ft_calc_figure(fig, rt, &ray);
				if (res)
				{
					rt->buffer[count].distanse = ray.t1;
					rt->buffer[count].color = ray.color;
					count++;
				}
				else
				{
					rt->buffer[count].distanse = -1;
					rt->buffer[count].color = (t_rgb) {240, 240, 240};
					count++;
				}
				fig = fig->next;
			}
			ft_draw(rt, ray.x, ray.y);
			ray.x++;
		}
		ray.y++;
	}
}