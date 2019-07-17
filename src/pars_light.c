/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:22:39 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/10 13:22:40 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	*ft_pr_light(char *str)
{
	char	*fig;
	t_light	*light;

	light = ft_memalloc(sizeof(t_light));
	ft_bzero(light, sizeof(t_light));
		fig = ft_strstr(str, "pos");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	light->pos = ft_get_pos_fig(fig);
	fig = ft_strstr(str, "color");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	light->color = ft_get_rgb_fig(fig);
		fig = ft_strstr(str, "intense");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	light->intense = ft_get_radius_fig(fig);
	if (light->intense > 1.0 || light->intense < 0)
		ft_print_error(BAD_LIGHT_INTS);
	return (light);
}

void	ft_pars_light(char *str, t_rtv1 *rt)
{
	char		*res;
	char		*light;
	int32_t		i;
	t_light		*lig;

	light = str;
	i = 0;
	while (light[i] != '\0')
	{
		if (light[i] >= 97 && light[i] <= 122)
		{
			if ((res = ft_strnstr(&light[i], "light", 7)))
			{
				lig = ft_pr_light(res);
				if (lig != NULL)
					ft_add_light_list(lig, rt);
			}
		}
		i++;
	}
}