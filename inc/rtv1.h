/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:59:17 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/06/27 10:59:21 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <fcntl.h>
#include "libft.h"
#include "error.h"

#define WIDTH 1280
#define HEIGHT 900
#define	HALFWIDTH WIDTH / 2
#define	HALFHEIGHT HEIGHT / 2
#define	DIST (double)WIDTH * 1.3
#define CLIP 0.5f
#define	X 0
#define	Y 1
#define	Z 2

typedef double t_vector __attribute__ ((vector_size (32)));


enum	e_figure
{
	plane,
	sphere,
	cylinder,
	cone
};

typedef	struct	s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

typedef	struct	s_sphere
{
	t_vector		pos;
	int32_t			radius;
}					t_shere;

typedef	struct	s_cam
{
	t_vector		pos;
	t_vector		direct;
	t_vector		vector;
	int32_t			len_ray;
}					t_cam;

typedef	struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_surf;
	SDL_Event	event;
}				t_sdl;

typedef	struct	s_figure
{
	enum e_figure		figure;
	void				*figure_data;
	struct	s_figure	*next;
}				t_figure;

typedef	struct	s_ray
{
	int32_t		x;
	int32_t		y;
	t_vector	start;
	t_vector	end;
	t_vector	vec;

}				t_ray;

typedef	struct	s_rtv1
{
	t_cam		camera;
	t_figure	figure;
	t_sdl		sdl;
}				t_rtv1;

void			ft_sdl_init(t_rtv1 *rt);

void			ft_sdlloop(t_rtv1 *rt);

void			ft_key(t_rtv1 *rt, int8_t *run);

void			ft_print_error(char *str);

void			ft_lddline(t_line **list, char *content);

t_line			*ft_lnewline(char *content);

void			ft_ldel(t_line **list);

void			ft_read(char *file, t_rtv1 *rt);

t_cam			ft_pars_cams(char *str);

void		ft_vec_normailize(t_vector *vec);

t_vector	ft_vec_add_len(t_vector vec, double len);

double		ft_vec_scalar(t_vector vec1, t_vector vec2);

t_vector	ft_vec_cross(t_vector vec1, t_vector vec2);

t_vector	ft_vec_sub(t_vector vec1, t_vector vec2);


#endif
