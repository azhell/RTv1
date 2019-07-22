/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_figure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:08:25 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/02 17:08:27 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int32_t	ft_inter_sphere(t_rtv1 *rt, t_ray *ray, t_sphere *sphere)
{
	t_inter					inter;

	double					result;

	inter.vec = ray->cam_pos - sphere->pos;
	inter.a = ft_vec_scalar(ray->ray, ray->ray);
	inter.b = ft_vec_scalar(inter.vec, ray->ray) * 2.0;
	inter.c = ft_vec_scalar(inter.vec, inter.vec) - sphere->radius * sphere->radius;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (0);
	ray->t1 = (-inter.b - sqrtf(result)) / (2.0 * inter.a);
	return (1);
}

int32_t	ft_inter_plane(t_rtv1 *rt, t_ray *ray, t_plane *plane)
{
	t_inter		inter;

	double		result;

	inter.a = ft_vec_scalar(plane->normal, plane->pos);
	inter.b = ft_vec_scalar(plane->normal, ray->cam_pos);
	inter.c = ft_vec_scalar(plane->normal, ray->ray);
	result = (inter.a - inter.b) / inter.c;
	if (result < 0.0001)
		return (0);
	ray->t1 = result;
	return (1);
}

int32_t	ft_inter_cap(t_rtv1 *rt, t_ray *ray, t_plane *plane)
{
	t_inter		inter;
	static	t_calc_light	calc_rgb;
	double		result;

	inter.a = ft_vec_scalar(plane->normal, plane->pos);
	inter.b = ft_vec_scalar(plane->normal, ray->cam_pos);
	inter.c = ft_vec_scalar(plane->normal, ray->ray);
	result = (inter.a - inter.b) / inter.c;
	if (result < 0.0001)
		return (0);
	ray->t1 = result;
	calc_rgb.flag_plane = 1;
	calc_rgb.point = ray->cam_pos + ft_vec_add_scale(ray->ray, result);
	calc_rgb.normal = plane->normal;
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.id = plane->id;
	ray->light = &calc_rgb;
	return (2);
}

int32_t		ft_check_cap(t_rtv1 *rt, t_ray *ray, void *fig, t_inter *inter)
{
	t_plane		plane;
	t_cone		*cone;

	cone = fig;
	if (inter->t1 > inter->t2 && inter->dist1 < inter->dist2)
	{
		if (inter->m2 < 0.0 || inter->m1 > cone->size)
			return (0);
		if (inter->m2 > cone->size)
		{
			plane.id = cone->id;
			plane.normal = -cone->rot;
			plane.pos = cone->pos + cone->size * -cone->rot;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}
	else 
	{
		if (inter->m1 < 0.0 || inter->m2 > cone->size)
			return (0);
		if (inter->m2 < 0.0)
		{
			plane.id = cone->id;
			plane.normal = cone->rot;
			plane.pos = cone->pos;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}
	return (1);
}


int32_t	ft_inter_cylinder(t_rtv1 *rt, t_ray *ray, t_cylinder *cylinder)
{
	t_inter					inter;
	double					result;
	int8_t					ret;

	inter.dist = ft_vec_sub(ray->cam_pos, cylinder->pos);
	inter.a = ft_vec_scalar(ray->ray, ray->ray) - powf(ft_vec_scalar(ray->ray, cylinder->rot), 2);
	inter.b = (ft_vec_scalar(ray->ray, inter.dist) - (ft_vec_scalar(ray->ray, cylinder->rot)
	* ft_vec_scalar(inter.dist, cylinder->rot))) * 2.0;
	inter.c = ft_vec_scalar(inter.dist, inter.dist) - powf(ft_vec_scalar(inter.dist, cylinder->rot), 2)
	- cylinder->radius * cylinder->radius;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (0);
	inter.t1 = (-inter.b + sqrtf(result)) / (inter.a * 2.0);
	inter.t2 = (-inter.b - sqrtf(result)) / (inter.a * 2.0);
	inter.m1 = ft_vec_scalar(ray->ray, cylinder->rot * inter.t1) + ft_vec_scalar(inter.dist, cylinder->rot);
	inter.m2 = ft_vec_scalar(ray->ray, cylinder->rot * inter.t2) + ft_vec_scalar(inter.dist, cylinder->rot);
	inter.dist1 = ft_vec_len(ray->cam_pos, cylinder->pos + cylinder->size * cylinder->rot);
	inter.dist2 = ft_vec_len(ray->cam_pos, cylinder->pos);
	inter.flag_cone = 0;
	ret = ft_check_cap(rt, ray, cylinder, &inter);
	if (ret == 2)
		return (2);
	else if (ret == 0)
		return (0);
	if (inter.t1 > inter.t2)
		inter.t1 = inter.t2;
	ray->m1 = inter.m1;
	ray->t1 = inter.t1;
	return (1);
}


int32_t		ft_inter_cone(t_rtv1 *rt, t_ray *ray, t_cone *cone)
{
	t_inter		inter;
	double		result;
		static	t_calc_light	calc_rgb;
	int8_t		ret;

	inter.k = cone->radius / cone->size;
	inter.dist = ft_vec_sub(ray->cam_pos, cone->pos);
	inter.a = ft_vec_scalar(ray->ray, ray->ray) - (1.0 + inter.k * inter.k)
	* powf(ft_vec_scalar(ray->ray, cone->rot), 2);
	inter.b = (ft_vec_scalar(ray->ray, inter.dist) - (1.0 + inter.k * inter.k)
	* (ft_vec_scalar(ray->ray, cone->rot) * ft_vec_scalar(inter.dist, cone->rot))) * 2.0;
	inter.c = ft_vec_scalar(inter.dist, inter.dist) - (1.0 + inter.k * inter.k)
	* powf(ft_vec_scalar(inter.dist, cone->rot), 2);
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (0);
	inter.t1 = (-inter.b + sqrtf(result)) / (inter.a * 2.0);
	inter.t2 = (-inter.b - sqrtf(result)) / (inter.a * 2.0);
	inter.m1 = ft_vec_scalar(ray->ray, cone->rot * inter.t1) + ft_vec_scalar(inter.dist, cone->rot);
	inter.m2 = ft_vec_scalar(ray->ray, cone->rot * inter.t2) + ft_vec_scalar(inter.dist, cone->rot);
	inter.dist1 = ft_vec_len(ray->cam_pos, cone->pos + cone->size * cone->rot);
	inter.dist2 = ft_vec_len(ray->cam_pos, cone->pos);
	inter.flag_cone = 1;
	ret = ft_check_cap(rt, ray, cone, &inter);
	if (ret == 2)
		return (2);
	else if (ret == 0)
		return (0);
	if (inter.t1 > inter.t2)
		inter.t1 = inter.t2;
	ray->t1 = inter.t1;
	ray->k = inter.k;
	ray->m1 = inter.m1;
	inter.d = inter.k * cone->radius;
	return (1);

}