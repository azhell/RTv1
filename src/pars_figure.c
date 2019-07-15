/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_figure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:42:49 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/29 19:42:50 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane		*ft_parse_plane(char *str)
{
	char		*fig;
	t_plane		*plane;

	plane = ft_memalloc(sizeof(t_plane));
	ft_bzero(plane, sizeof(t_plane));
	fig = ft_strstr(str, "pos");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	plane->pos = ft_get_pos_fig(fig);
	fig = ft_strstr(str, "color");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	plane->color = ft_get_rgb_fig(fig);
	fig = ft_strstr(str, "normal");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	plane->normal = ft_get_pos_fig(fig);
	printf("%f %f %f \n", plane->pos[X], plane->pos[Y], plane->pos[Z]);
	printf("%d %d %d \n", plane->color.r, plane->color.g, plane->color.b);
	printf("%f %f %f \n", plane->normal[X], plane->normal[Y], plane->normal[Z]);
	return (plane);
}

t_sphere	*ft_parse_sphere(char *str)
{
	char		*fig;
	t_sphere	*sphere;

	sphere = ft_memalloc(sizeof(t_sphere));
	ft_bzero(sphere, sizeof(t_sphere));
	fig = ft_strstr(str, "pos");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	sphere->pos = ft_get_pos_fig(fig);
	fig = ft_strstr(str, "color");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	sphere->color = ft_get_rgb_fig(fig);
	fig = ft_strstr(str, "radius");
	if (fig == NULL)
		ft_print_error(BAD_FIGURE_POS);
	sphere->radius = ft_get_radius_fig(fig);
	//printf("%f %f %f \n", sphere->pos[X], sphere->pos[Y], sphere->pos[Z]);
	printf("%d %d %d \n", sphere->color.r, sphere->color.g, sphere->color.b);

	return (sphere);
}

// t_sphere	*ft_get_sphere(char *str)
// {
// 	return (NULL);
// }

// t_cylinder	*ft_get_cylinder(char *str)
// {

// }

// t_plane		*ft_get_plane(char *str)
// {

// }

// t_cone		*ft_get_cone(char *str)
// {

// }

void		ft_pars_figure(char *str, t_rtv1 *rt)
{
	char		*figure;
	char		*res;
	t_figure	*fig;
	t_all_fig	*sv;
	int32_t		i;

	figure	= str;
	i = 0;
	sv = ft_memalloc(sizeof(t_all_fig));
	while (figure[i] != '\0')
	{
		if (figure[i] >= 97 && figure[i] <= 122)
		{
			if ((res = ft_strnstr(&figure[i], "sphere", 7)))
			{
				sv->sphere = ft_parse_sphere(res);
				if (sv->sphere != NULL)
				{
					ft_add_fig_list(sv, rt);
					sv->sphere = NULL;
				}
			}
		}
		if (figure[i] >= 97 && figure[i] <= 122)
		{
			if ((res = ft_strnstr(&figure[i], "plane", 5)))
			{
				sv->plane = ft_parse_plane(res);
				if (sv->plane != NULL)
				{
					ft_add_fig_list(sv, rt);
					sv->plane = NULL;
				}
			}
		}
		i++;
	}
	fig = rt->figure;
	free(sv);
}