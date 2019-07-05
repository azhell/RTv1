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

int32_t		ft_get_radius_fig(char *str)
{
	int32_t	i;
	int32_t	result;

	i = 1;
	result = 10;
	while (str[i] != '\0')
	{
		if ((str[i] >= 47 && str[i] <= 57) && str[i - 1])
		{
			result = ft_atoi(&str[i]);
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
		if ((str[i] >= 47 && str[i] <= 57) && str[i - 1])
		{
			pos[count] = ft_atoi(&str[i]);
		//	printf("%d %f\n", ft_atoi(&str[i]), pos[count]);
			while (str[i] != '\0' && str[i] >= 47 && str[i] <= 57)
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

	i = 1;
	count = 0;
	pos[X] = 0;
	pos[Y] = 0;
	pos[Z] = 0;
	while (str[i] != '\0')
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
		i++;
	}
	rgb.r = pos[0];
	rgb.g = pos[1];
	rgb.b = pos[2];
	return (rgb);
}