/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 19:27:26 by pmartin           #+#    #+#             */
/*   Updated: 2017/04/29 17:58:31 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		PERLIN_H
# define	PERLIN_H
# include "../libft/includes/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <stdio.h>

#define BUMP 1
#define WOOD 2
#define MARBLE 4
#define CHELOU 8

typedef				struct s_vec t_vec;
typedef				struct s_grid
{
	int				grad[16][3];
	int				perm[512];
	int				o;
}					t_grid;

typedef				struct s_double
{
	__int64_t		inte;
	double			doub;
}					t_double;

typedef				struct s_perlin
{
	double			g00[8];
	double			uvw[3];
	double			x[4];
	double			y[2];
	t_double		z;
	t_double		xyz[3];
}					t_perlin;

typedef				struct s_config_perlin
{
	double			f;
	int				octave;
	double			persistence;
	double			amplitude;
}					t_config_perlin;

typedef				struct s_sdl
{
	SDL_Texture		*sdl_tex;
	SDL_Window		*sdl_win;
	SDL_Renderer	*sdl_ren;
	SDL_Event		event;
	SDL_Surface		*surface;
	int				height;
	int				width;
	int				x;
	int				y;
}					t_sdl;

double				dot_product(int *grad, double x, double y, double z);
int					*grad(t_grid *grid, int x, int y, int z);
void				int_double(double k, t_double *doub);
double				poly(double k);
double				inter_li(double a, double b, double t);
void				init(t_grid *grid);
double				ezperlin(t_vec *comp);
double				perlin_noise(double x, double y, double z);
void				get_n_perlined(t_vec *vec);
void				get_n_perlined2(t_vec *vec, t_vec *comp);
#endif
