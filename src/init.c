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
	void		*data;

	i = 0;
	while (i < THREAD)
	{
		count = 0;
		figure = rt->figure;
		while (count < rt->num_figure)
		{
			thread[i].figure[count].figure = figure->figure;
			thread[i].figure[count].figure_id = figure->figure_id;
			data = ft_memalloc(figure->size);
			thread[i].figure[count].figure_data =
			ft_memcpy(data, figure->figure_data, figure->size);
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
	t_light		*light;
	t_light_stack	tmp;


	i = 0;
	while (i < THREAD)
	{
		count = 0;
		light = rt->light;
		while (count < rt->num_light)
		{

			thread[i].light[count] = *(t_light_stack*)
			ft_memcpy(&thread[i].light[count], light, sizeof(t_light_stack));
			// thread[i].light[count].intense = light->intense;
			// thread[i].light[count].type = light->type;
			// thread[i].light[count].color = light->color;
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
	int32_t				count;

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
	ft_sdlloop(rt, thread);

	i = 0;
	//clear leaks
	while (i < THREAD)
	{
		count = 0;
		while (count < rt->num_figure)
		{
			free(thread[i].figure[count].figure_data);
			count++;
		}
	i++;
	}
}
