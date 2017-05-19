/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_make_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 02:02:51 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/17 21:04:53 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_dist(t_vec *a, t_vec *b)
{
	return (sqrt(ft_sq(b->x - a->x) + ft_sq(b->y - a->y)
				+ ft_sq(b->z - a->z)));
}

void		make_wood(t_var *var, double coef, t_obj *cur, t_light *light)
{
	double g;

	g = 20 * perlin_noise(var->pt.x * 0.1,
					 var->pt.y * 0.1,
					 var->pt.z * 0.1);
	g = g - (__int64_t)g;
	g = g * 3.14159265359;
	g = (1 - cos(g));
	var->colorf.r += coef * light->color.r * (g * cur->mat.color1.r
		+ (1.0 - g) * cur->mat.color2.r);
	var->colorf.g += coef * light->color.g * (g * cur->mat.color1.g
		+ (1.0 - g) * cur->mat.color2.g);
	var->colorf.b += coef * light->color.b * (g * cur->mat.color1.b
		+ (1.0 - g) * cur->mat.color2.b);
}

void		make_marble(t_var *var, double coef, t_obj *cur, t_light *light)
{
	double	c;
	double	g;
	int 	lvl;

	lvl = 0;
	c = 0;
	g = 0;
	while (lvl < 10)
	{
		g = perlin_noise(var->pt.x * 0.5 * (double)lvl,
						var->pt.y * 0.5 * (double)lvl,
						var->pt.z * 0.5 * (double)lvl);
		if (g < 0)
			g *= -1;
		c += (1.0 / (double)lvl) * g;
		lvl++;
	}
	var->colorf.r += coef * light->color.r * (g * cur->mat.color1.r
		+ (1.0 - g) * cur->mat.color2.r);
	var->colorf.g += coef * light->color.g * (g * cur->mat.color1.g
		+ (1.0 - g) * cur->mat.color2.g);
	var->colorf.b += coef * light->color.b * (g * cur->mat.color1.b
		+ (1.0 - g) * cur->mat.color2.b);
}

void		makecolor(t_var *var, double coef, t_obj *cur, t_light *light)
{
	if (coef <= 0)
		return ;
	if (cur->mat.perlin & WOOD)
		make_wood(var, coef, cur, light);
	else if (cur->mat.perlin & MARBLE)
		make_marble(var, coef, cur, light);
	else if (cur->text)
		make_text(var, coef, cur, light);
	else
	{
		var->colorf.r += coef * light->color.r * cur->color.r;
		var->colorf.g += coef * light->color.g * cur->color.g;
		var->colorf.b += coef * light->color.b * cur->color.b;
	}
	if (var->colorf.r > 1.0)
		var->colorf.r = 1;
	if (var->colorf.g > 1.0)
		var->colorf.g = 1;
	if (var->colorf.b > 1.0)
		var->colorf.b = 1;
}

void		makecolor2(t_var *var, double coef, t_light *light)
{
	if (coef < 0)
		return ;
	var->colorf.r += coef * light->color.r;
	var->colorf.g += coef * light->color.g;
	var->colorf.b += coef * light->color.b;
	if (var->colorf.r > 1.0)
		var->colorf.r = 1;
	if (var->colorf.g > 1.0)
		var->colorf.g = 1;
	if (var->colorf.b > 1.0)
		var->colorf.b = 1;
}
