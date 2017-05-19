/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:35:41 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 18:56:52 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_sq(double a)
{
	return (a * a);
}

void		ft_pixel_put(t_var *var, int color)
{
	double d;
	double r;
	double g;
	double b;

	color = ((((int)var->colorf.r) * 256) << 16)
	  + ((((int)var->colorf.g) * 256) << 8) + ((int)var->colorf.b) * 256;
	r = 112.0 / 255.0;
	g = 66.0 / 255.0;
	b = 20.0 / 255.0;
	d = (var->colorf.r + var->colorf.g + var->colorf.b) / 3;
	if (var->filter == 0 || var->filter == 3)
		color = (int)(var->colorf.r * 255) * 65536
			+ (int)(var->colorf.g * 255) * 256
			+ (int)(var->colorf.b * 255);
	 else if (var->filter == 1)
		color = (int)(d * 187) * 65536
			+ (int)(d * 187) * 256
			+ (int)(d * 187);
	else if (var->filter == 2)
		color = (int)(d * r * 255) * 65536
			+ (int)(d * g * 255) * 256
			+ (int)(d * b * 255);
	ft_memcpy(var->surface->pixels + (var->imgy)
			  * var->surface->pitch
			  + var->imgx * 4, &color, 3);
}

void		ft_printvec(t_vec *vec, char *s)
{
	printf("%s X == %g Y == %g Z == %g\n", s, vec->x, vec->y, vec->z);
}
