/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:59:43 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 10:59:44 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*ft_create_str(t_line *lst)
{
	char	*str;
	char	*tmp;
	t_line	*ltmp;

	str = ft_memalloc(sizeof(char));
	ltmp = lst;
	while (lst)
	{
		tmp = str;
		str = ft_strjoin(tmp, lst->content);
		free(tmp);
		lst = lst->next;
	}
	ft_ldel(&ltmp);
	return (str);
}

t_line	*ft_read_file(char *file)
{
	int32_t	fd;
	char	*line;
	int8_t	count;
	t_line	*list;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		ft_print_error(BAD_FD);
	while (get_next_line(fd, &line) > 0)
	{
		if (count == 0)
			list = ft_lnewline(line);
		else
			ft_lddline(&list, line);
		count++;
		free(line);
	}
	close(fd);
	return(list);
}

void	ft_read(char *file, t_rtv1 *rt)
{
	t_line	*lst;
	char	*str;
	char	*cam;
	char	*obj;
	char	*light;

	lst = ft_read_file(file);
	str = ft_create_str(lst);
	cam = ft_strstr(str, "cam");
	if (cam == NULL)
		ft_print_error(ERROR_CAM_INIT);
	obj = ft_strstr(str, "obj");
	if (obj == NULL)
		ft_print_error(NOT_FOUND_FIGURE);
	light = ft_strstr(str, "light");
	if (light == NULL)
		ft_print_error(NOL_FOUND_LIGHT);
	ft_pars_light(light, rt);
	rt->camera = ft_pars_cams(cam);
	ft_pars_figure(obj, rt);
	free(str);
}