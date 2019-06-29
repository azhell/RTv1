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

char	*ft_read(char *file)
{
	int32_t	fd;
	char	*line;
	int		count;
	t_line	*list;

	count = 0;
	if((fd = open(file, O_RDONLY) < 0))
		ft_print_error(BAD_FD);
	get_next_line(fd, &line);
	{
		// if (count == 0)
		// 	list = ft_lnewline(line);
		// else
		// 	ft_lddline(&list, line);
		// printf("%s \n", line);
		// count++;
		//free(line);
		//return(NULL);
	}
	return(NULL);
}