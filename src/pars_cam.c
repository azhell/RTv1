/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:28:00 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/29 17:28:04 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_normalize_vec(t_cam *cam)
{
	t_vector	vec;
	float		len;
	float		inversion;

	vec = cam->vector;
	len = sqrt(pow(vec[X], 2) + pow(vec[Y], 2) + pow(vec[Z], 2));
	inversion = 1.0 / len;
	cam->vector[X] = vec[X] * inversion;
	cam->vector[Y] = vec[Y] * inversion;
	cam->vector[Z] = vec[Z] * inversion;
}

void	ft_set_cam_pos(t_cam *cam, char *str)
{
	int32_t	i;
	uint8_t	count;

	i = 1;
	count = 0;
	if (!(str = ft_strstr(str, "pos")))
		ft_print_error(ERROR_CAM_INIT);
	while (str[i] != '\0')
	{
		if ((str[i] >= 47 && str[i] <= 57) && str[i - 1])
		{
			cam->pos[count] = ft_atoi(&str[i]);
			while (str[i] != '\0' && str[i] >= 47 && str[i] <= 57)
				i++;
			i--;
			count++;
		}
		if (count == 3)
			break ;
		i++;
	}
}

void	ft_set_cam_dir(t_cam *cam, char *str)
{
	int32_t	i;
	uint8_t	count;

	i = 1;
	count = 0;
	if (!(str = ft_strstr(str, "direct")))
		ft_print_error(ERROR_CAM_INIT);
	while (str[i] != '\0')
	{
		if ((str[i] >= 47 && str[i] <= 57) && str[i - 1])
		{
			cam->vector[count] = ft_atoi(&str[i]);
			while (str[i] != '\0' && str[i] >= 47 && str[i] <= 57)
				i++;
			i--;
			count++;
		}
		if (count == 3)
			break ;
		i++;
	}
}
t_cam	ft_pars_cams(char *str)
{
	t_cam	camera;
	char	*cam;
	int32_t	i;

	i = 0;
	if (!(cam = ft_strstr(str, "cam")))
		ft_print_error(ERROR_CAM_INIT);
	ft_set_cam_pos(&camera, cam);
	ft_set_cam_dir(&camera, cam);
	ft_normalize_vec(&camera);
//	printf("%f %f %f \n", camera.pos[X], camera.pos[Y], camera.pos[Z]);
//	printf("%f %f %f \n", camera.vector[X], camera.vector[Y], camera.vector[Z]);
	return (camera);
}