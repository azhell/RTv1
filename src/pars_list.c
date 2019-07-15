/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:03:49 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/07/02 13:03:51 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_figure	*ft_lst_fig_new(t_all_fig *sv)
{
	t_figure	*figure;

	figure = ft_memalloc(sizeof(t_figure));
	if (sv->cone != NULL)
	{
		figure->figure = cone;
		figure->figure_data = sv->cone;
	}
	else if (sv->plane != NULL)
	{
		figure->figure = plane;
		figure->color = &sv->plane->color;
		figure->figure_data = sv->plane;
	}
	else if (sv->cylinder != NULL)
	{
		figure->figure = cylinder;
		figure->figure_data = sv->cylinder;
	}
	else if (sv->sphere != NULL)
	{
		figure->figure = sphere;
		figure->color = &sv->sphere->color;
		figure->figure_data = sv->sphere;
	}
	return (figure); //<- pizdec blyt'''''''''''''' ~!!!!!!!~!!~~!~!~!~!~!~!~
}

void	ft_add_fig_back(t_figure *main, t_figure *add)
{
	t_figure	*tmp;

	tmp = main;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = add;
}

void	ft_add_fig_list(t_all_fig *sv, t_rtv1 *rt)
{
	t_figure	*tmp_lst;
	t_figure	*add_back;

	tmp_lst = rt->figure;
	if (rt->figure == NULL)
		rt->figure = ft_lst_fig_new(sv);
	else
	{
		tmp_lst = rt->figure;
		add_back = ft_lst_fig_new(sv);
		ft_add_fig_back(tmp_lst, add_back);
		//rt->figure = tmp_lst;
	}
}

void	ft_add_light_list(t_light *light, t_rtv1 *rt)
{
	t_light	*tmp_lst;

	tmp_lst = rt->light;
	if (rt->light == NULL)
	{
		rt->light = light;
	}
	else
	{
		tmp_lst = rt->light;
		while (tmp_lst->next)
			tmp_lst = tmp_lst->next;	
		tmp_lst->next = light;
	}
}