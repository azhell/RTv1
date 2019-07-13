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

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <fcntl.h>
# include "libft.h"
# include "error.h"

# define WH 500
# define HT 500
# define HALFWIDTH WIDTH / 2.0
# define HALFHEIGHT HEIGHT / 2.0
# define DIST (double)WIDTH * 1.3
# define CLIP 0.5f
# define X 0
# define Y 1
# define Z 2
# define KEK printf("!!!!!!!!!!!!!!!!!!!!!!\n")
# define ADR(x) printf("%p \n", x);

typedef	double	t_vector __attribute__ ((vector_size (32)));

typedef	struct	s_rgb
{
	int8_t		r;
	int8_t		g;
	int8_t		b;
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

typedef	struct		s_normal
{
	double			t;
	t_vector		p;
	t_vector		normal;
}					t_normal;

typedef	struct		s_cone
{
	t_rgb			color;
	t_vector		pos;
	double			radius;
}					t_cone;

typedef	struct		s_cylinder
{
	t_vector		pos;
	t_rgb			color;
	double			radius;
}					t_cylinder;

typedef	struct		s_inter
{
	double			a;
	double			b;
	double			c;
	t_vector		d;
}					t_inter;

typedef	struct		s_color
{
	t_vector		pos1;
	t_vector		pos2;
}					t_color;

typedef	struct		s_sphere
{
	t_vector		pos;
	t_rgb			color;
	double			radius;
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
	enum e_figure	figure;
	t_rgb			*color;
	void			*figure_data;
	struct s_figure	*next;
}					t_figure;

typedef	struct		s_light
{
	t_rgb			color;
	t_vector		pos;
	struct s_light	*next;
}					t_light;

typedef	struct	s_ray
{
	float_t			u;
	float_t			v;
	int32_t			x;
	int32_t			y;
	t_rgb			color;
	t_vector		ray;
	t_normal		normal;
	float_t			res;
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
	t_vector		horizontal;
	t_vector		vertical;
	t_vector		left_corner;
}					t_data_ray;

typedef	struct		s_rtv1
{
	t_cam			camera;
	t_data_ray		data;
	t_figure		*figure;
	t_light			*light;
	t_sdl			sdl;
}					t_rtv1;

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

t_vector		ft_vec_normalize(t_vector vec);

t_vector		ft_vec_add_scale(t_vector vec, double len);

double			ft_vec_scalar(t_vector vec1, t_vector vec2);

t_vector		ft_vec_cross(t_vector vec1, t_vector vec2);

t_vector		ft_vec_sub(t_vector vec1, t_vector vec2);

t_vector		ft_get_pos_fig(char *str);

t_rgb			ft_get_rgb_fig(char *str);

int32_t			ft_get_radius_fig(char *str);

void			ft_pars_figure(char *str, t_rtv1 *rt);

void			ft_put_pixel_rgb(t_rtv1 *rt, int x, int y, t_rgb *col);

void			ft_start_rt(t_rtv1 *rt);

void			ft_init(t_rtv1 *rt);

float			ft_inter_sphere(double rad, t_vector p, t_rtv1 *rt, t_ray *r);

t_figure		*ft_lst_fig_new(t_all_fig *sv);

void			ft_add_fig_list(t_all_fig *sv, t_rtv1 *rt);

void			ft_add_light_list(t_light *light, t_rtv1 *rt);

void			ft_pars_light(char *str, t_rtv1 *rt);

t_rgb			ft_get_color(t_ray *ray, t_rtv1 *rt, t_rgb *figure);

#endif
