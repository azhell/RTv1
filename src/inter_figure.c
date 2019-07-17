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

t_calc_light	*ft_inter_sphere(t_sphere *sphere, t_rtv1 *rt, t_ray *ray)
{
	t_inter					inter;
	static	t_calc_light	calc_rgb;
	double					result;

	inter.vec = rt->camera.pos - sphere->pos;
	inter.a = ft_vec_scalar(ray->ray, ray->ray);
	inter.b = ft_vec_scalar(inter.vec, ray->ray) * 2.0;
	inter.c = ft_vec_scalar(inter.vec, inter.vec) - sphere->radius * sphere->radius;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (NULL);
	ray->t1 = (-inter.b - sqrtf(result)) / (2.0 * inter.a);
	calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
	calc_rgb.normal = (calc_rgb.point - sphere->pos) / (t_vector) {sphere->radius, sphere->radius, sphere->radius};
	calc_rgb.normal = ft_vec_normalize(calc_rgb.normal);
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
	calc_rgb.flag_plane = 0;
	calc_rgb.id = sphere->id;
	return (&calc_rgb);
}

t_calc_light	*ft_inter_plane(t_rtv1 *rt, t_ray *ray, t_plane *plane)
{
	t_inter		inter;
	static	t_calc_light	calc_rgb;
	double		result;

	inter.a = ft_vec_scalar(plane->normal, plane->pos);
	inter.b = ft_vec_scalar(plane->normal, rt->camera.pos);
	inter.c = ft_vec_scalar(plane->normal, ray->ray);
	result = (inter.a - inter.b) / inter.c;
	if (result < 0.0001)
		return (NULL);
	ray->t1 = result;
	calc_rgb.flag_plane = 1;
	calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, result);
	calc_rgb.normal = plane->normal;
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
	calc_rgb.id = plane->id;
	return (&calc_rgb);
}

t_calc_light	*ft_inter_cap(t_rtv1 *rt, t_ray *ray, t_plane *plane)
{
	t_inter		inter;
	static	t_calc_light	calc_rgb;
	double		result;

	inter.a = ft_vec_scalar(plane->normal, plane->pos);
	inter.b = ft_vec_scalar(plane->normal, rt->camera.pos);
	inter.c = ft_vec_scalar(plane->normal, ray->ray);
	result = (inter.a - inter.b) / inter.c;
	if (result < 0.0001)
		return (NULL);
	ray->t1 = result;
	calc_rgb.flag_plane = 0;
	calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, result);
	calc_rgb.normal = plane->normal;
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
	calc_rgb.id = plane->id;
	return (&calc_rgb);
}

t_calc_light	*ft_inter_cylinder(t_rtv1 *rt, t_ray *ray, t_cylinder *cylinder)
{
	t_inter					inter;
	static	t_calc_light	calc_rgb;
	double					result;
	t_plane					plane;

	inter.dist = ft_vec_sub(rt->camera.pos, cylinder->pos);
	inter.a = ft_vec_scalar(ray->ray, ray->ray) - powf(ft_vec_scalar(ray->ray, cylinder->rot), 2);
	inter.b = (ft_vec_scalar(ray->ray, inter.dist) - (ft_vec_scalar(ray->ray, cylinder->rot)
	* ft_vec_scalar(inter.dist, cylinder->rot))) * 2.0;
	inter.c = ft_vec_scalar(inter.dist, inter.dist) - powf(ft_vec_scalar(inter.dist, cylinder->rot), 2)
	- cylinder->radius * cylinder->radius;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (NULL);

	inter.t1 = (-inter.b + sqrtf(result)) / (inter.a * 2.0);
	inter.t2 = (-inter.b - sqrtf(result)) / (inter.a * 2.0);
	inter.m1 = ft_vec_scalar(ray->ray, cylinder->rot * inter.t1) + ft_vec_scalar(inter.dist, cylinder->rot);
	inter.m2 = ft_vec_scalar(ray->ray, cylinder->rot * inter.t2) + ft_vec_scalar(inter.dist, cylinder->rot);

	inter.dist1 = ft_vec_len(rt->camera.pos, cylinder->pos + cylinder->size * cylinder->rot);
	inter.dist2 = ft_vec_len(rt->camera.pos, cylinder->pos);
	if (inter.t1 > inter.t2 && inter.dist1 < inter.dist2) ///о я ебу костыли //  убейте меня !
	{
		if (inter.m2 < 0.0 || inter.m1 > cylinder->size)
			return (NULL);
		if (inter.m2 > cylinder->size)
		{
			plane.id = cylinder->id;
			plane.normal = cylinder->rot;
			plane.pos = cylinder->pos + cylinder->size * cylinder->rot;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}
	else
	{
		if (inter.m1 < 0.0 || inter.m2 > cylinder->size)
			return (NULL);
		if (inter.m2 < 0.0)
		{
			plane.normal = -cylinder->rot;
			plane.pos = cylinder->pos;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}

	calc_rgb.flag_plane = 0;
	if (inter.t1 > inter.t2)
		inter.t1 = inter.t2;
	ray->t1 = inter.t1;
	calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, inter.t1);
	calc_rgb.normal = ft_vec_normalize(calc_rgb.point - (cylinder->pos )- cylinder->rot * inter.m1);
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.id = cylinder->id;
	calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);

	return (&calc_rgb);
}

t_calc_light	*ft_inter_cone(t_rtv1 *rt, t_ray *ray, t_cone *cone)
{
	t_inter		inter;
	static	t_calc_light	calc_rgb;
	double		result;
	t_plane		plane;

	inter.k = cone->radius / cone->size;

	inter.dist = ft_vec_sub(rt->camera.pos, cone->pos);

	inter.a = ft_vec_scalar(ray->ray, ray->ray) - (1.0 + inter.k * inter.k)
	* powf(ft_vec_scalar(ray->ray, cone->rot), 2);

	inter.b = (ft_vec_scalar(ray->ray, inter.dist) - (1.0 + inter.k * inter.k)
	* (ft_vec_scalar(ray->ray, cone->rot) * ft_vec_scalar(inter.dist, cone->rot))) * 2.0;

	inter.c = ft_vec_scalar(inter.dist, inter.dist) - (1.0 + inter.k * inter.k)
	* powf(ft_vec_scalar(inter.dist, cone->rot), 2);

	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (NULL);
	inter.t1 = (-inter.b + sqrtf(result)) / (inter.a * 2.0);
	inter.t2 = (-inter.b - sqrtf(result)) / (inter.a * 2.0);
	inter.m1 = ft_vec_scalar(ray->ray, cone->rot * inter.t1) + ft_vec_scalar(inter.dist, cone->rot);
	inter.m2 = ft_vec_scalar(ray->ray, cone->rot * inter.t2) + ft_vec_scalar(inter.dist, cone->rot);
	// if (inter.m1 < 0.0 || inter.m2 > cone->size)
	// 	return (NULL);
	inter.dist1 = ft_vec_len(rt->camera.pos, cone->pos + cone->size * cone->rot);
	inter.dist2 = ft_vec_len(rt->camera.pos, cone->pos);
	if (inter.t1 > inter.t2 && inter.dist1 < inter.dist2) ///о я ебу костыли //  убейте меня !
	{
		if (inter.m2 < 0.0 || inter.m1 > cone->size)
			return (NULL);
		if (inter.m2 > cone->size)
		{
			plane.id = cone->id;
			plane.normal = cone->rot;
			plane.pos = cone->pos + cone->size * cone->rot;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}
	else
	{
		if (inter.m1 < 0.0 || inter.m2 > cone->size)
			return (NULL);
		if (inter.m2 < 0.0)
		{
			plane.normal = cone->rot;
			plane.pos = cone->pos;
			return (ft_inter_cap(rt, ray, &plane));
		}
	}
	if (inter.t1 > inter.t2)
		inter.t1 = inter.t2;
	ray->t1 = inter.t1;
	inter.d = inter.k * cone->radius;

	calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, inter.t1);
	calc_rgb.normal = ft_vec_normalize(calc_rgb.point - cone->pos - cone->rot * inter.m1 -
	cone->rot * inter.d * inter.k * inter.k);
	calc_rgb.ray_vec = ray->ray;
	calc_rgb.id = cone->id;
	calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
	return (&calc_rgb);

}