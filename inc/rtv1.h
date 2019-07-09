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

<<<<<<< HEAD
#define WH 1280
#define HT 900
=======
#define WH 500
#define HT 500
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
#define	HALFWIDTH WIDTH / 2
#define	HALFHEIGHT HEIGHT / 2
#define	DIST (double)WIDTH * 1.3
#define CLIP 0.5f
#define	X 0
#define	Y 1
#define	Z 2
#define	KEK printf("!!!!!!!!!!!!!!!!!!!!!!\n")
#define	ADR(x) printf("%p \n", x);

typedef double t_vector __attribute__ ((vector_size (32)));


typedef	struct	s_rgb
{
	int16_t		r;
	int16_t		g;
	int16_t		b;
}				t_rgb;

enum	e_figure
{
	plane,
	sphere,
	cylinder,
	cone
};

typedef	struct		s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

typedef	struct		s_plane
{
	t_vector		pos;
	t_rgb			color;
}					t_plane;

typedef	struct		s_cone
{
	t_rgb			color;
	t_vector		pos;
<<<<<<< HEAD
	double			radius;
=======
	float_t			radius;
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
}					t_cone;

typedef	struct		s_cylinder
{
	t_vector		pos;
	t_rgb			color;
<<<<<<< HEAD
	double			radius;
=======
	float_t			radius;
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
}					t_cylinder;

typedef	struct		s_inter
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_inter;


typedef	struct		s_sphere
{
	t_vector		pos;
	t_rgb			color;
<<<<<<< HEAD
	double			radius;
=======
	float_t			radius;
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
}					t_sphere;

typedef	struct		s_cam
{
	t_vector		pos;
	t_vector		direct;
	t_vector		vector;
	int32_t			len_ray;
}					t_cam;

typedef	struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*win_surf;
	SDL_Event		event;
}					t_sdl;

typedef	struct		s_figure
{
	enum e_figure		figure;
	void				*figure_data;
	struct	s_figure	*next;
}					t_figure;

typedef	struct		s_ligth
{
	t_rgb			color;
	t_vector		pos;
	struct	s_ligth	*next;
}					t_ligth;

typedef	struct	s_ray
{
	float_t			u;
	float_t			v;
	int32_t			x;
	int32_t			y;
<<<<<<< HEAD
	t_vector		color;
	t_vector		ray;
=======
	t_vector		vec;

>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
}				t_ray;

typedef	struct		s_all_fig
{
	t_sphere		*sphere;
	t_cone			*cone;
	t_cylinder		*cylinder;
	t_plane			*plane;
}					t_all_fig;

typedef	struct		s_data_ray
{
<<<<<<< HEAD
	t_sphere		*sphere;
	t_cone			*cone;
	t_cylinder		*cylinder;
	t_plane			*plane;
}				t_all_fig;
=======
	t_vector		horizontal;
	t_vector		vertical;
	t_vector		left_corn;
}					t_data_ray;
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447


typedef	struct		s_rtv1
{
	t_cam			camera;
<<<<<<< HEAD
	t_figure		*figure;
	t_sdl			sdl;
	t_vector		horizontal;
	t_vector		vertical;
	t_vector		left_corner;
}				t_rtv1;
=======
	t_data_ray		data;
	t_figure		*figure;
	t_sdl			sdl;
}					t_rtv1;
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447

void			ft_sdl_init(t_rtv1 *rt);

void			ft_init(t_rtv1 *rt);

void			ft_sdlloop(t_rtv1 *rt);

void			ft_key(t_rtv1 *rt, int8_t *run);

void			ft_print_error(char *str);

void			ft_lddline(t_line **list, char *content);

t_line			*ft_lnewline(char *content);

void			ft_ldel(t_line **list);

void			ft_read(char *file, t_rtv1 *rt);

t_cam			ft_pars_cams(char *str);

t_vector		ft_vec_normailize(t_vector vec);

<<<<<<< HEAD
t_vector		ft_vec_scale(t_vector vec, double len);
=======
t_vector		ft_vec_add_scale(t_vector vec, double len);
>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447

double			ft_vec_scalar(t_vector vec1, t_vector vec2);

t_vector		ft_vec_cross(t_vector vec1, t_vector vec2);

t_vector		ft_vec_sub(t_vector vec1, t_vector vec2);

t_vector		ft_get_pos_fig(char *str);

t_rgb			ft_get_rgb_fig(char *str);

int32_t			ft_get_radius_fig(char *str);

void			ft_pars_figure(char *str, t_rtv1 *rt);

<<<<<<< HEAD
void			ft_put_pixel_rgb(t_rtv1 *rt, int x, int y, t_rgb col);

void			ft_start_rt(t_rtv1 *rt);

void			ft_init(t_rtv1 *rt);

float			ft_inter_sphere(double rad, t_vector pos, t_rtv1 *rt, t_ray *ray);

t_figure		*ft_lst_fig_new(t_all_fig *sv);

void			ft_add_fig_list(t_all_fig *sv, t_rtv1 *rt);

=======
void			ft_vec_normailize(t_vector *vec);

void			ft_put_pixel_rgb(t_rtv1 *rt, int x, int y, t_rgb *col);

void			ft_start_rt(t_rtv1 *rt);

void			ft_add_fig_list(t_all_fig *sv, t_rtv1 *rt);

double			ft_inter_sphere(t_vector pos, float radius, t_ray *ray, t_rtv1 *rt);

>>>>>>> 6320ac8dc155134b6b7dff6525aec653e8045447
#endif
