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

float_t	ft_inter_sphere(double rad, t_vector pos, t_rtv1 *rt, t_ray *ray)
{
	t_inter	inter;
	double	result;
	double	t;

	inter.d = rt->camera.pos - pos;
	inter.a = ft_vec_scalar(ray->ray, ray->ray);
	inter.b = ft_vec_scalar(inter.d, ray->ray) * 2.0;
	inter.c = ft_vec_scalar(inter.d, inter.d) - rad * rad;
	result = (inter.b * inter.b) - (4.0 * inter.a * inter.c);
	t = (-inter.b - sqrt(inter.b * inter.b - inter.a * inter.c)) / inter.a;
	if (result > 0)
	{
		ray->normal.t = t;
		ray->normal.p = rt->camera.pos + ft_vec_add_scale(ray->ray, t);
		ray->normal.normal = (ray->normal.p - pos) / (t_vector) {rad, rad, rad};
		ray->normal.normal = ft_vec_normalize(ray->normal.normal);

		res = ft_vec_scalar();
	}
	return (result);
}
