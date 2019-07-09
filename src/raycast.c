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
		if (result)
		{
			ray->color.r = fig.sphere->color.r;
			ray->color.g = fig.sphere->color.g;
			ray->color.b = fig.sphere->color.b;
		}
		fig.sphere = NULL;
		//printf("%f\n", result);
		return (result > 0);
	}
	return (0);
}
// 	double	v;

// 	u = (WIN_W - (double)x * 2.0) / WIN_H;
// 	v = (WIN_H - (double)y * 2.0) / WIN_W;
// 	K = ft_vectorsub(&mlx->cam_dir, &mlx->cam_pos); //scalar vector
// 	ft_vectornorm(&K);  ///  normalaze
// 	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
// 	ft_vectornorm(&I);
// 	J = ft_vectorcross(&I, &K);
// 	mlx->ray_dir = (t_vec){u * I.x + v * J.x + FOV * K.x, u * I.y + v * J.y
// 		+ FOV * K.y, u * I.z + v * J.z + FOV * K.z};
// 	ft_vectornorm(&mlx->ray_dir);
// 	mlx->cpt = 0;
// 	ft_fzero(tab, 4);
// 	return (tab);
// }

void	ft_gen_ray(t_rtv1 *rt, t_ray *ray)
{
	double	u, v;
	t_vector	tab;
	t_vector	corn;
	t_vector	dir;

	v = (double)(WH - ray->x * 5.0) / (double)HT;
	u = (double)(HT - ray->y * 5.0) / (double)HT;
	corn = (t_vector) 	{0.0, 1.0, 0.0};

	rt->camera.vector = ft_vec_sub(rt->camera.direct, rt->camera.pos);
	//	printf("%f %f %f \n", rt->camera.vector[X], rt->camera.vector[Y], rt->camera.vector[Z]);
	rt->camera.vector = ft_vec_normalize(rt->camera.vector);

	tab = ft_vec_cross(rt->camera.vector, corn);
	tab = ft_vec_normalize(tab);
	dir = ft_vec_cross(rt->camera.vector, tab);
	ray->ray[X] = u * tab[X] + v * dir[X] + 2.0 * rt->camera.vector[X];
	ray->ray[Y] = u * tab[Y] + v * dir[Y] + 2.0 * rt->camera.vector[Y];
	ray->ray[Z] = u * tab[Z] + v * dir[Z] + 2.0 * rt->camera.vector[Z];
	ray->ray = ft_vec_normalize(ray->ray);
	//printf("%f %f %f \n", ray->ray[X], ray->ray[Y], ray->ray[Z]);
}

void	ft_start_rt(t_rtv1 *rt)
{
	t_ray		ray;
	t_rgb		rgb;
	t_figure	*fig;
//	double		u, v;
	float		res;

	ray.y = 0;
	while (ray.y < HT)
	{
		ray.x = 0;
		while (ray.x < WH)
		{
			fig = rt->figure;
		//	u = (float)ray.x / (float)WH;
		//	v = (float)ray.y / (float)HT;
			rgb.r = 34;
			rgb.g = 50;
			rgb.b = 39;
		//	ray.ray = rt->data.left_corner + rt->data.horizontal * u  + rt->data.vertical * v;
		//	printf("%f %f %f %f %f\n", ray.ray[X], ray.ray[Y], ray.ray[Z], rt->horizontal[X] * u, rt->vertical[Y] * v);
			ft_gen_ray(rt, &ray);
			while (fig)
			{
				res = ft_calc_figure(fig, rt, &ray);
				if (res)
				{
					rgb.r = ray.color.r;
					rgb.g = ray.color.g;
					rgb.b = ray.color.b;
					break ;
				}
				else
				{
					rgb.r = 20;
					rgb.g = 20;
					rgb.b = 20;
				}

				fig = fig->next;
			}
			ft_put_pixel_rgb(rt, ray.x, ray.y, &rgb);
			ray.x++;
		}
		ray.y++;
	}
}