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

int32_t	ft_calc_figure(t_figure_stack *figure, t_thread *rt, t_ray *ray, int32_t num)
{
	printf("%u | ", figure->figure);

	if (figure->figure == sphere)
		if (ft_calc_sphere((t_sphere*)&figure->figure_data, rt, ray))
		{
			ft_light(rt->light, ray, rt);
			return (1);
		}
	// if (figure->figure == plane)
	// 	if (ft_calc_plane((t_plane*)&figure->figure_data, rt, ray))
	// 	{
	// 		ft_light(rt->light, ray, rt);
	// 		return (1);
	// 	}
	if (figure->figure == cylinder)
		if (ft_calc_cylinder((t_cylinder*)&figure->figure_data, rt, ray))
		{
		//	ft_light(rt->light, ray, rt);
			return (1);
		}
	if (figure->figure == cone)
		if (ft_calc_cone((t_cone*)&figure->figure_data, rt, ray))
		{
		//	ft_light(rt->light, ray, rt);
			return (1);
		}
	return (0);
}

void	ft_gen_ray(t_thread *rt, t_ray *ray)
{
	double		u;
	double		v;
	t_vector	tab;
	t_vector	corn;
	t_vector	dir;

	v = (double)(WH - ray->x * 2.0) / (double)WH;
	u = (double)(HT - ray->y * 2.0) / (double)WH;
	corn = (t_vector) {0.0, 1.0, 0.0};
	rt->cam->vector = ft_vec_sub(rt->cam->direct, rt->cam->pos);
	rt->cam->vector = ft_vec_normalize(rt->cam->vector);
	tab = ft_vec_cross(rt->cam->vector, corn);
	tab = ft_vec_normalize(tab);
	dir = ft_vec_cross(rt->cam->vector, tab);
	ray->ray[X] = u * tab[X] + v * dir[X] + 2.0 * rt->cam->vector[X];
	ray->ray[Y] = u * tab[Y] + v * dir[Y] + 2.0 * rt->cam->vector[Y];
	ray->ray[Z] = u * tab[Z] + v * dir[Z] + 2.0 * rt->cam->vector[Z];
	ray->ray = ft_vec_normalize(ray->ray);
}

void	ft_solve_ray(t_thread *rt, t_ray *ray)
{
	size_t			count;
	float			res;
	size_t			i;

	count = 0;
	res = 0;
	i = 0;
	while (i < rt->num_figure)
	{
		res = ft_calc_figure(&rt->figure[i], rt, ray, i);
		if (res)
		{
			rt->buffer[count].distanse = ray->t1;
			rt->buffer[count].color = ray->color;
			count++;
		}
		else
		{
			rt->buffer[count].distanse = -1;
			rt->buffer[count].color = (t_rgb) {250, 250, 250};
			count++;
		}
		i++;
	}
}

void	ft_start_rt_t(t_thread *rt)
{
	t_ray		ray;

	ray.x = rt->y;
	ray.cam_pos = rt->cam->pos;
	ray.y = 0;
	while (ray.y < HT)
	{
		ray.x = rt->y;
		while (ray.x < rt->y_end)
		{
			ft_gen_ray(rt, &ray);
			ft_solve_ray(rt, &ray);
			ft_draw(rt, ray.x, ray.y);
			ray.x++;
		}
		ray.y++;
	}
}

void	ft_set_xy(t_thread *thead, uint32_t count)
{
	int32_t	diff;
	int32_t y_start;
	int32_t y_end;

	diff = WH / THREAD;
	y_start = diff * count;
	y_end = y_start + diff;
	thead->y = y_start;
	thead->y_end = y_end;
}

void	ft_start_rt_thread(t_rtv1 *rt, t_thread *thread)
{
	pthread_t	th[THREAD];
	uint32_t	count;
	void		(*rt_start)	(t_thread*);

	rt_start = ft_start_rt_t;
	count = -1;
	thread->rt = rt;
	while (++count < THREAD)
	{
		thread[count].n_thr = count;
		thread[count].rt = rt;
		ft_set_xy(&thread[count], count);
		pthread_create(&th[count], NULL, (void*)rt_start, &thread[count]);
	}
	count = 0;
	while (count < THREAD)
		pthread_join(th[count++], NULL);
}
