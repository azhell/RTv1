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

t_figure	*ft_lst_fig_new(t_all_fig *sv, size_t id)
{
	t_figure	*figure;

	figure = ft_memalloc(sizeof(t_figure));
	if (sv->cone != NULL)
	{
		sv->cone->id = id;
		figure->figure = cone;
		figure->figure_id = id;
		figure->figure_data = sv->cone;
		figure->size = sizeof(t_cone);
	}
	else if (sv->plane != NULL)
	{
		sv->plane->id = id;
		figure->figure = plane;
		figure->figure_id = id;
		figure->figure_data = sv->plane;
		figure->size = sizeof(t_plane);
	}
	else if (sv->cylinder != NULL)
	{
		sv->cylinder->id = id;
		figure->figure = cylinder;
		figure->figure_id = id;
		figure->figure_data = sv->cylinder;
		figure->size = sizeof(t_cylinder);
	}
	else if (sv->sphere != NULL)
	{
		sv->sphere->id = id;
		figure->figure = sphere;
		figure->figure_id = id;
		figure->figure_data = sv->sphere;
		figure->size = sizeof(t_sphere);
	}
	return (figure); //<- pizdec blyt'''''''''''''' ~!!!!!!!~!!~~!~!~!~!~!~!~
}

void	ft_add_fig_back(t_figure *main, t_figure *add)
{
	t_figure	*tmp;

	tmp = main;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
}

void	ft_add_fig_list(t_all_fig *sv, t_rtv1 *rt, size_t id)
{
	t_figure	*tmp_lst;
	t_figure	*add_back;

	tmp_lst = rt->figure;
	if (rt->figure == NULL)
		rt->figure = ft_lst_fig_new(sv, id);
	else
	{
		tmp_lst = rt->figure;
		add_back = ft_lst_fig_new(sv, id);
		ft_add_fig_back(tmp_lst, add_back);
	}
}

void	ft_add_light_list(t_light *light, t_rtv1 *rt)
{
	t_light	*tmp_lst;

	tmp_lst = rt->light;
	if (rt->light == NULL)
		rt->light = light;
	else
	{
		tmp_lst = rt->light;
		while (tmp_lst->next)
			tmp_lst = tmp_lst->next;
		tmp_lst->next = light;
	}
}