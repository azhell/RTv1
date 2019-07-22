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

int32_t	ft_calc_figure(t_figure *figure, t_rtv1 *rt, t_ray *ray)
{
	if (figure->figure == sphere)
		if (ft_calc_sphere((t_sphere*)figure->figure_data, rt, ray))
		{
			ft_light(rt->light, ray, rt);
			return (1);
		}
	if (figure->figure == plane)
		if (ft_calc_plane((t_plane*)figure->figure_data, rt, ray))
		{
			ft_light(rt->light, ray, rt);
			return (1);
		}
	if (figure->figure == cylinder)
		if (ft_calc_cylinder((t_cylinder*)figure->figure_data, rt, ray))
		{
			ft_light(rt->light, ray, rt);
			return (1);
		}
	if (figure->figure == cone)
		if (ft_calc_cone((t_cone*)figure->figure_data, rt, ray))
		{
			ft_light(rt->light, ray, rt);
			return (1);
		}
	return (0);
}

void	ft_gen_ray(t_rtv1 *rt, t_ray *ray)
{
	double		u;
	double		v;
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

void	ft_solve_ray(t_rtv1 *rt, t_ray *ray, int8_t th)
{
	size_t		count;
	float		res;
	t_figure	*fig;

	count = 0;
	fig = rt->figure;
	res = 0;
	while (fig)
	{
		res = ft_calc_figure(fig, rt, ray);
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
		fig = fig->next;
	}
}

void	ft_start_rt_t(t_thread *voda)
{
	t_ray		ray;
	t_rtv1		*rt;

	rt = voda->rt;
	ray.x = voda->y;
	ray.cam_pos = rt->camera.pos;
	ray.y = 0;
	while (ray.y < HT)
	{
		ray.x = voda->y;
		while (ray.x < voda->y_end)
		{
			ft_gen_ray(rt, &ray);
			ft_bzero(rt->buffer, rt->size);
			ft_solve_ray(rt, &ray, voda->n_thr);
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
