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

<<<<<<< HEAD
float_t	ft_inter_sphere(double rad, t_vector pos, t_rtv1 *rt, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	result;
	t_vector d;

	d = rt->camera.pos - pos;
	a = ft_vec_scalar(ray->ray, ray->ray);
	b = ft_vec_scalar(d, ray->ray) * 3.0;
	c = ft_vec_scalar(d, d) - rad * rad;
	result = (b * b) - (4.0 * a * c);
	return (result);
}
=======
double		ft_inter_sphere(t_vector pos, float radius, t_ray *ray, t_rtv1 *rt)
{
	t_vector vec_p;
	t_inter	sphere;
	double	result;

	vec_p = rt->camera.pos - pos;
	sphere.a = ft_vec_scalar(ray->vec, ray->vec);
	sphere.b = ft_vec_scalar(vec_p, ray->vec) * 2.0;
	sphere.c = ft_vec_scalar(vec_p, vec_p) - radius * radius; 
	result = (sphere.b * sphere.b) - (4.0 * sphere.a * sphere.c);
	return	(result);
}
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
