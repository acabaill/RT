/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 13:31:28 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/12 13:39:45 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	perlin2(t_perlin *perlin, t_grid *grid)
{
	perlin->uvw[0] = poly(perlin->xyz[0].doub);
	perlin->uvw[1] = poly(perlin->xyz[1].doub);
	perlin->uvw[2] = poly(perlin->xyz[2].doub);
	perlin->g00[0] = dot_product(grad(grid, perlin->xyz[0].inte,
	perlin->xyz[1].inte,perlin->xyz[2].inte), perlin->xyz[0].doub,
	perlin->xyz[1].doub, perlin->xyz[2].doub);
	perlin->g00[1] = dot_product(grad(grid, perlin->xyz[0].inte,
	perlin->xyz[1].inte, perlin->xyz[2].inte + 1), perlin->xyz[0].doub,
	perlin->xyz[1].doub , perlin->xyz[2].doub - 1.);
	perlin->g00[2] = dot_product(grad(grid, perlin->xyz[0].inte,
	perlin->xyz[1].inte + 1, perlin->xyz[2].inte), perlin->xyz[0].doub,
	perlin->xyz[1].doub -1., perlin->xyz[2].doub);
	perlin->g00[3] = dot_product(grad(grid, perlin->xyz[0].inte,
	perlin->xyz[1].inte + 1, perlin->xyz[2].inte + 1), perlin->xyz[0].doub,
	perlin->xyz[1].doub - 1., perlin->xyz[2].doub - 1.);
	perlin->g00[4] = dot_product(grad(grid, perlin->xyz[0].inte + 1,
	perlin->xyz[1].inte, perlin->xyz[2].inte), perlin->xyz[0].doub -1.,
	perlin->xyz[1].doub, perlin->xyz[2].doub);
	perlin->g00[5] = dot_product(grad(grid, perlin->xyz[0].inte + 1,
	perlin->xyz[1].inte, perlin->xyz[2].inte + 1), perlin->xyz[0].doub - 1.,
	perlin->xyz[1].doub, perlin->xyz[2].doub - 1.);
	perlin->g00[6] = dot_product(grad(grid, perlin->xyz[0].inte + 1,
	perlin->xyz[1].inte + 1, perlin->xyz[2].inte), perlin->xyz[0].doub - 1.,
	perlin->xyz[1].doub - 1., perlin->xyz[2].doub);
}

double		perlin_noise(double x, double y, double z)
{
	static t_grid		grid;
	t_perlin			perlin;
	int					i;
	int					j;

	i = 0;
	j = 0;
	if (!grid.o)
		init(&grid);
	int_double(x, &perlin.xyz[0]);
	int_double(y, &perlin.xyz[1]);
	int_double(z, &perlin.xyz[2]);
	perlin2(&perlin, &grid);
	perlin.g00[7] = dot_product(grad(&grid, perlin.xyz[0].inte + 1,
	perlin.xyz[1].inte + 1, perlin.xyz[2].inte + 1), perlin.xyz[0].doub - 1.,
	perlin.xyz[1].doub -1., perlin.xyz[2].doub - 1.);
	perlin.x[0] = inter_li(perlin.g00[0], perlin.g00[4], perlin.uvw[0]);
	perlin.x[1] = inter_li(perlin.g00[2], perlin.g00[6], perlin.uvw[0]);
	perlin.x[2] = inter_li(perlin.g00[1], perlin.g00[5], perlin.uvw[0]);
	perlin.x[3] = inter_li(perlin.g00[3], perlin.g00[7], perlin.uvw[0]);
	perlin.y[0] = inter_li(perlin.x[0], perlin.x[1], perlin.uvw[1]);
	perlin.y[1] = inter_li(perlin.x[2], perlin.x[3], perlin.uvw[1]);
	perlin.z.doub = inter_li(perlin.y[0], perlin.y[1], perlin.uvw[2]);
	return (perlin.z.doub);
}

double	ezperlin2(double x, double y, double z, t_config_perlin *conf)
{
	double	o;
	double	f;
	double	ampli;
	int 	i;

	i = 0;
	o = 0;
	f = 1;
	ampli = 1.0;
	while (i < conf->octave)
	{
		o += perlin_noise(x * f, y * f, z * f)
			* ampli;
		ampli *= conf->persistence;
		f *= 2.0;
		i++;
	}
	f = (1.0 - conf->persistence) / (1.0 - ampli);

	return (o * f);
}

void	get_n_perlined2(t_vec *n, t_vec *comp)
{
	n->x *= (perlin_noise(comp->x, comp->y, comp->z) + 1);
	n->y *= (perlin_noise(comp->y, comp->z, comp->x) + 1);
	n->z *= (perlin_noise(comp->z, comp->x, comp->y) + 1);
}

void	get_n_perlined(t_vec *n)
{
	double			a;
	double			b;
	double			c;
	t_config_perlin conf;

	conf.persistence  = 0.1;
	conf.octave = 20;
	a =	ezperlin2(n->x, n->y, n->z, &conf) + 1;
	b =	ezperlin2(n->y, n->z, n->x, &conf) + 1;
	c =	ezperlin2(n->z, n->x, n->y, &conf) + 1;
	n->x *= a;
	n->y *= b;
	n->z *= c;
}

double	ezperlin(t_vec *comp)
{
	t_config_perlin conf;

	conf.persistence  = 0.2;
	conf.octave = 10;
	return ((ezperlin2(comp->x, comp->y
					   , comp->z, &conf) + 1) / 2);
}
