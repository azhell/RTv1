/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:03:22 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 11:03:24 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_put_pixel_rgb(t_rtv1 *rt, int x, int y, t_rgb col)
{
	int32_t		*target_pixel;
	int32_t		color;

	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
		return ;
	target_pixel = rt->sdl.win_surf->pixels + y *
			rt->sdl.win_surf->pitch + x *
			rt->sdl.win_surf->format->BytesPerPixel;

	color = SDL_MapRGB(rt->sdl.win_surf->format, col.r, col.g, col.b);
	*target_pixel = -color;
}


void		ft_vec_normailize(t_vector *vec)
{
	float		len;
	float		inversion;

	len = sqrt(pow((*vec)[X], 2) + pow((*vec)[Y], 2) + pow((*vec)[Z], 2));
	inversion = 1.0 / len;
	(*vec)[X] = (*vec)[X] * inversion;
	(*vec)[Y] = (*vec)[Y] * inversion;
	(*vec)[Z] = (*vec)[Z] * inversion;
}

t_vector	ft_vec_add_scale(t_vector vec, double len)
{
	t_vector	result;

	result[X] = vec[X] * len;
	result[Y] = vec[Y] * len;
	result[Z] = vec[Z] * len;
	return (result);
}

double		ft_vec_scalar(t_vector vec1, t_vector vec2)
{
	double	result;

	result = vec1[X] * vec2[X] + vec1[Y] * vec2[Y] + vec1[Z] * vec2[Z];
	return (result);
}

t_vector	ft_vec_cross(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result[X] = vec1[Y] * vec2[Z] - vec1[Z] * vec2[Y];
	result[Y] = vec1[Z] * vec2[X] - vec1[X] * vec2[Z];
	result[Z] = vec1[X] * vec2[Y] - vec1[Y] * vec2[X];
	return (result);
}

t_vector	ft_vec_sub(t_vector vec1, t_vector vec2)
{
	return (vec1 - vec2);
}

void		ft_print_error(char *str)
{
	ft_putendl(str);
	exit(100);
}