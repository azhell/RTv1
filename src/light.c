/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:08:44 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/10 14:08:47 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int8_t	ft_shadows(t_thread *rt, t_shadow *sh)
{
	t_figure_stack	*fig;
	t_ray		ray;
	int32_t		i;

	fig = rt->figure;
	i = 0;
	ray.ray = *sh->vec;
	ray.cam_pos = *sh->pos;
	while (i < rt->num_figure)
	{
		if (sh->id != fig[i].figure_id)
		{
			if (fig[i].figure == sphere)
				if (ft_inter_sphere(&ray, (t_sphere*)fig[i].figure_data))
					return (1);
			if (fig[i].figure == plane)
				if (ft_inter_plane(&ray, (t_plane*)fig[i].figure_data))
					return (1);
			if (fig[i].figure == cylinder)
				if (ft_inter_cylinder(&ray, (t_cylinder*)fig[i].figure_data))
					return (1);
			if (fig[i].figure == cone)
				if (ft_inter_cone(&ray, (t_cone*)fig[i].figure_data))
					return (1);
		}
		i++;
	}
	return (0);
}

void	ft_light(t_light_stack *light, t_ray *ray, t_thread *rt)
{
	double			angle_lht;
	double			angle_cam;
	double			color_i;
	double			len_N;
	double			len_R;
	t_vector		vec_light;
	t_vector		vec;
	t_shadow		shadow;

	color_i = 0.2;
	vec = ft_vec_normalize(light[0].pos - ray->light->point);
	vec_light = ft_vec_normalize(ray->light->point - light[0].pos);
	angle_lht = ft_vec_scalar(vec_light, -ray->light->normal);
	angle_cam = ft_vec_scalar(ray->ray, ray->light->normal);
	if (ray->light->flag_plane == 1)
		angle_lht = fabs(angle_lht);
	len_N = ft_vec_len(ray->light->point, light[0].pos);
	len_R = ft_vec_len(rt->cam->pos, ray->light->point);
	shadow.vec = &vec;
	shadow.pos = &ray->light->point;
	shadow.id = ray->light->id;
	shadow.len = len_N;
	{
		int32_t res = ft_shadows(rt, &shadow);
		if (!res && angle_lht > 0)
			color_i += rt->light[0].intense * angle_lht / (len_N * len_R / 900);
		if (color_i > 1.0)
			color_i = 1.0;
		if (color_i < 0.0)
			color_i = 0;
		ray->color.r = ray->color.r * color_i;
		ray->color.g = ray->color.g * color_i;
		ray->color.b = ray->color.b * color_i;
	}
}