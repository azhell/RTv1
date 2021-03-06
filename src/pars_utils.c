/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:26:16 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/01 17:26:18 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double_t	ft_get_radius_fig(char *str)
{
	int32_t	i;
	double	result;

	i = 1;
	result = 10;
	while (str[i] != '\0')
	{
		if (((str[i] >= 47 && str[i] <= 57) && str[i - 1]) || str[i] == '-')
		{
			result = ft_atof(&str[i]);
			return (result);
		}
		i++;
	}
	return (result);
}

t_vector	ft_get_pos_fig(char *str)
{
	t_vector	pos;
	int32_t		i;
	int8_t		count;

	i = 1;
	count = 0;
	pos[X] = 0;
	pos[Y] = 0;
	pos[Z] = 0;
	while (str[i] != '\0')
	{
		if (((str[i] >= 47 && str[i] <= 57) && str[i - 1]) || str[i] == '-')
		{
			pos[count] = ft_atof(&str[i]);
			while ((str[i] != '\0' && str[i] >= 47 && str[i] <= 57)
			|| str[i] == '-')
				i++;
			i--;
			count++;
		}
		if (count == 3)
			return (pos);
		i++;
	}
	return (pos);
}

t_rgb		ft_get_rgb_fig(char *str)
{
	t_vector	pos;
	t_rgb		rgb;
	int32_t		i;
	int8_t		count;

	i = 0;
	count = 0;
	pos = (t_vector) {0, 0, 0};
	while (str[++i] != '\0')
	{
		if ((str[i] >= 47 && str[i] <= 57) && str[i - 1])
		{
			pos[count] = ft_atoi(&str[i]);
			while (str[i] != '\0' && str[i] >= 47 && str[i] <= 57)
				i++;
			i--;
			count++;
		}
		if (count == 3)
			break ;
	}
	rgb.r = (int8_t)pos[0];
	rgb.g = (int8_t)pos[1];
	rgb.b = (int8_t)pos[2];
	return (rgb);
}
