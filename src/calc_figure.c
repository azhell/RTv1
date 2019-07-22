/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_figure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:55:14 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/18 16:55:15 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int32_t	ft_calc_sphere(t_sphere *sphere, t_rtv1 *rt, t_ray *ray)
{
	static	t_calc_light	calc_rgb;

	ray->color = sphere->color;
	if (ft_inter_sphere(rt, ray, sphere))
	{
		calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
		calc_rgb.normal = (calc_rgb.point - sphere->pos) / (t_vector) {sphere->radius, sphere->radius, sphere->radius};
		calc_rgb.normal = ft_vec_normalize(calc_rgb.normal);
		calc_rgb.ray_vec = ray->ray;
		calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
		calc_rgb.flag_plane = 0;
		calc_rgb.id = sphere->id;
		ray->light = &calc_rgb;
		ft_light(rt->light, ray, rt);
			return (1);
	}
	return (0);
}


int32_t	ft_calc_plane(t_plane *plane, t_rtv1 *rt, t_ray *ray)
{
	static	t_calc_light	calc_rgb;

	ray->color = plane->color;
	if (ft_inter_plane(rt, ray, plane))
	{
		calc_rgb.flag_plane = 1;
		calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
		calc_rgb.normal = plane->normal;
		calc_rgb.ray_vec = ray->ray;
		calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
		calc_rgb.id = plane->id;
		ray->light = &calc_rgb;
		ft_light(rt->light, ray, rt);
			return (1);
	}
	return (0);
}


int32_t	ft_calc_cone(t_cone *cone, t_rtv1 *rt, t_ray *ray)
{
	static	t_calc_light	calc_rgb;
	int8_t	ret;
	double	d;

	ray->color = cone->color;
	ret = ft_inter_cone(rt, ray, cone);
	if (ret == 1)
	{
		d = ray->k * cone->radius;
		calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
		calc_rgb.normal = ft_vec_normalize(calc_rgb.point - cone->pos - cone->rot * ray->m1 -
		cone->rot * d * ray->k * ray->k);
		calc_rgb.ray_vec = ray->ray;
		calc_rgb.id = cone->id;
		calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
		ray->light = &calc_rgb;
		calc_rgb.flag_plane = 0;
		ft_light(rt->light, ray, rt);
		return (1);
	}
	else if (ret == 2)
	{
		ft_light(rt->light, ray, rt);
		return (1);
	}
	return (0);
}

int32_t	ft_calc_cylinder(t_cylinder *cylinder, t_rtv1 *rt, t_ray *ray)
{
	static	t_calc_light	calc_rgb;
	int8_t	ret;

	ray->color = cylinder->color;
	ret = ft_inter_cylinder(rt, ray, cylinder);
	if (ret == 1)
	{
		calc_rgb.flag_plane = 0;
		calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
		calc_rgb.normal = ft_vec_normalize(calc_rgb.point - (cylinder->pos )- cylinder->rot * ray->m1);
		calc_rgb.ray_vec = ray->ray;
		calc_rgb.id = cylinder->id;
		calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
		ray->light = &calc_rgb;
		ft_light(rt->light, ray, rt);
		return (1);
	}
	else if (ret == 2)
	{
		ft_light(rt->light, ray, rt);
		return (1);
	}
	return (0);
}