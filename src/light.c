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
	// t_figure	*fig;
	// t_ray		ray;

	// fig = rt->figure;
	// ray.ray = *sh->vec;
	// ray.cam_pos = *sh->pos;
	// while (fig)
	// {
	// 	if (fig->figure == sphere && sh->id != fig->figure_id)
	// 		if (ft_inter_sphere(rt, &ray, (t_sphere*)fig->figure_data))
	// 		{
	// 			return (1);
	// 		}
	// 	if (fig->figure == plane && sh->id != fig->figure_id)
	// 		if (ft_inter_plane(rt, &ray, (t_plane*)fig->figure_data))
	// 			return (1);

	// 	if (fig->figure == cylinder && sh->id != fig->figure_id)
	// 		if (ft_inter_cylinder(rt, &ray, (t_cylinder*)fig->figure_data))
	// 			return (1);

	// 	if (fig->figure == cone && sh->id != fig->figure_id)
	// 		if (ft_inter_cone(rt, &ray, (t_cone*)fig->figure_data))
	// 			return (1);
	// 	fig = fig->next;
	// }
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
//	printf("%f %f || ", angle_lht, angle_cam);
	if (ray->light->flag_plane == 1)
		angle_lht = fabs(angle_lht);
	len_N = ft_vec_len(ray->light->point, light[0].pos);
	len_R = ft_vec_len(rt->cam->pos, ray->light->point);
	// fix color after
	//printf("%f %f ", len_R, len_N);
	shadow.vec = &vec;
	shadow.pos = &ray->light->point;
	shadow.id = ray->light->id;
	shadow.len = len_N;
	//res = 0;
	//if (angle_lht > 0.0)
	{
	//	int32_t res = ft_shadows(rt, &shadow);
		int32_t	res = 0;
	//	color_i -= 1.0 - angle_lht;
	//	color_i -= DAMPING * len_N;
		if (!res && angle_lht > 0)
			color_i += rt->light[0].intense * angle_lht / (len_N * len_R / 900);
		if (color_i > 1.0)
			color_i = 1.0;
		if (color_i < 0.0)
			color_i = 0;
		ray->color.r = ray->color.r * color_i;
		ray->color.g = ray->color.g * color_i;
		ray->color.b = ray->color.b * color_i;
		// if ((fabs(angle_cam) - fabs(angle_lht)) < 0.01)
		// {
		// 	ray->color.r = 14;
		// 	ray->color.g = 23;
		// 	ray->color.b = 24;
		// }
	}
}