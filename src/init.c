/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:01:56 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/03 17:01:58 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_init_th_cam(t_rtv1 *rt, t_thread *thread)
{
	uint8_t	i;

	i = 0;
	while (i < THREAD)
	{
		thread[i].num_figure = rt->num_figure;
		thread[i].num_light = rt->num_light;
		thread[i].cam->pos = rt->camera.pos;
		thread[i].cam->direct = rt->camera.direct;
		thread[i].cam->vector = rt->camera.vector;
		i++;
	}
}

void	ft_init_th_figure(t_rtv1 *rt, t_thread *thread)
{
	int32_t		i;
	int32_t		count;
	t_figure	*figure;
	t_sphere	*sph;

	figure = rt->figure;
	i = 0;
	count = 0;
	while (i < THREAD)
	{
		while (count < rt->num_figure)
		{
			printf(" Id_X %u\n", figure->figure);
			thread->figure[i].figure = figure->figure;
			printf(" Id_Y  %u\n", 	thread->figure[i].figure);
			thread->figure[i].figure_id = figure->figure_id;
			ft_memcpy(&thread->figure[i].figure_data, figure->figure_data, figure->size);
			figure = figure->next;
			count++;
		}
		i++;
	}
}

void	ft_init_th_light(t_rtv1 *rt, t_thread *thread)
{
	uint8_t		i;
	uint8_t		count;
	t_light	*light;

	light = rt->light;
	i = 0;
	count = 0;
	while (i < THREAD)
	{
		while (count < rt->num_light)
		{
			thread->light[i].pos = light->pos;
			thread->light[i].intense = light->intense;
			thread->light[i].type = light->type;
			thread->light[i].color = light->color;
			light = light->next;
			count++;
		}
		i++;
	}
}

void	ft_init_th_sdl(t_rtv1 *rt, t_thread *thread)
{
	uint8_t	i;

	i = 0;
	while (i < THREAD)
	{
		thread[i].sdl = rt->sdl;
		i++;
	}
}

void	ft_init(t_rtv1 *rt)
{
	t_buffer	buffer[rt->num_figure];

	ft_bzero(buffer, rt->size);
	rt->buffer = buffer;
}

void	ft_mem_th_data_stack(t_rtv1 *rt, int8_t i)
{
	t_buffer			buffer[THREAD][rt->num_figure];
	t_thread			thread[THREAD];
	t_light_stack		light[THREAD][rt->num_light];
	t_figure_stack		figure[THREAD][rt->num_figure];
	t_cam				cam[THREAD];

	i = -1;
	while (++i < THREAD)
	{
		thread[i].figure = figure[i];
		thread[i].light = light[i];
		thread[i].cam = &cam[i];
		thread[i].buffer = buffer[i];
	}

	ft_init_th_sdl(rt, thread);
	ft_init_th_cam(rt, thread);
	ft_init_th_figure(rt, thread);
	ft_init_th_light(rt, thread);
	//printf("%f \n", thread[0].light[0].pos[]);
	ft_sdlloop(rt, thread);
}
