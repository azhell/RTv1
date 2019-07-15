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

t_calc_light	*ft_inter_sphere(double rad, t_vector pos, t_rtv1 *rt, t_ray *ray)
{
	t_inter			inter;
	static	t_calc_light	calc_rgb;
	double			result;

	inter.vec = rt->camera.pos - pos;
	inter.a = ft_vec_scalar(ray->ray, ray->ray);
	inter.b = ft_vec_scalar(inter.vec, ray->ray) * 2.0;
	inter.c = ft_vec_scalar(inter.vec, inter.vec) - rad * rad;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	if (result < 0)
		return (NULL);
	ray->t1 = (-inter.b - sqrt(result)) / (2.0 * inter.a);
	ray->t2 = (-inter.b + sqrt(result)) / (2.0 * inter.a);
	if (result > 0)
	{
		calc_rgb.point = rt->camera.pos + ft_vec_add_scale(ray->ray, ray->t1);
		calc_rgb.normal = (calc_rgb.point - pos) / (t_vector) {rad, rad, rad};
		calc_rgb.normal = ft_vec_normalize(calc_rgb.normal);
		calc_rgb.ray_vec = ray->ray;
		calc_rgb.light_vec = ft_vec_normalize(rt->light->pos - calc_rgb.point);
	}
	return (&calc_rgb);
}
 
double	ft_inter_plane(t_rtv1 *rt, t_ray *ray, t_plane *plane)
{
	t_inter					inter;
	//static	t_calc_light	calc_rgb;
	double	t;

	t = -1;
	inter.a = ft_vec_scalar(plane->normal, ray->ray);
//	printf("%f | ", inter.a);
	if (inter.a > 1e-6)
	{
		inter.vec = plane->pos - rt->camera.pos;
		t = ft_vec_scalar(inter.vec, plane->normal) / inter.a;
		// printf("%f | ", inter.a);
		ray->color = plane->color;
	}
	return (t >= 0);
}