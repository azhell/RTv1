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

void	ft_init(t_rtv1 *rt)
{
	rt->data.horizontal = (t_vector){4.0, 0.0, 0.0};
	rt->data.vertical = (t_vector){0.0, 2.0, 0.0};
	rt->data.left_corn = (t_vector){-2.0, -1.0, -1.0};
	rt->camera.vector = rt->camera.direct - rt->camera.pos;
	ft_vec_normailize(&rt->camera.vector);
	rt->data.left_corn = rt->camera.pos + rt->camera.vector;

//	printf("%f %f %f \n", rt->data.left_corn[X], rt->data.left_corn[Y], rt->data.left_corn[Z]);
}