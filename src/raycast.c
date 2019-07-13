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
		ray->color = fig.sphere->color;
		result = ft_inter_sphere(fig.sphere->radius, fig.sphere->pos, rt, ray);
		fig.sphere = NULL;
		return (result > 0);
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
	t_rgb		rgb;
	t_figure	*fig;
	float		res;

	ray.y = 0;
	while (ray.y < HT)
	{
		ray.x = 0;
		while (ray.x < WH)
		{
			fig = rt->figure;
			ft_gen_ray(rt, &ray);
			while (fig)
			{
				res = ft_calc_figure(fig, rt, &ray);
				if (res)
				{
					rgb = ray.color;
					break ;
				}
				else
					rgb = (t_rgb) {255, 255, 255};
				fig = fig->next;
			}
			ft_put_pixel_rgb(rt, ray.x, ray.y, &rgb);
			ray.x++;
		}
		ray.y++;
	}
}