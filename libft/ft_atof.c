/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:08:28 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/16 15:08:31 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_atof(const char *atof)
{
	int			i;
	int			k;
	double		sign;
	double		result;

	i = 0;
	k = 0;
	result = 0;
	while (atof[i] == ' ')
		i++;
	sign = (atof[i] == '-' ? -1 : 1);
	i += ((atof[i] == '-' || atof[i] == '+') ? 1 : 0);
	while (atof[i] && atof[i] == ' ')
		i++;
	while (atof[i] && atof[i] != '.' && atof[i] >= '0' && atof[i] <= '9')
		result = result * 10 + (atof[i++] - '0');
	i += ((atof[i] == '.') ? 1 : 0);
	while (atof[i + k] && (atof[i + k] >= '0' && atof[i + k] <= '9'))
		result = result * 10 + (atof[i + k++] - '0');
	while (k-- > 0)
		result /= 10;
	return (result * sign);
}
