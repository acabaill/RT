/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_vp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:36:05 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/14 14:41:33 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		initray(t_var *var)
{
	static double	x;
	static double	y;
	double			u;
	double			v;

	if (!x && !y)
	{
		x = WIDTH / var->sizex;
		y = (HEIGHT / var->sizey);
	}
	u = (double)var->imgx + var->x_alias;
	v = (double)var->imgy + var->y_alias;
	var->viewplane.v = var->viewplane.pos;
	var->viewplane.v.x += (var->cam.up.x * y * v)
		+ (var->cam.right.x * x * u);
	var->viewplane.v.y += (var->cam.up.y * y * v)
		+ (var->cam.right.y * x * u);
	var->viewplane.v.z += (var->cam.up.z * y * v)
		+ (var->cam.right.z * x * u);
//	ft_print3d(&var->viewplane.v, "Viewplane");
	ezvec(&var->cam.pos, &var->viewplane.v, &var->ray);
	normvec(&var->ray);
}

void		initviewplane(t_var *var)
{
	t_vec			tmp;
	t_vec			tmp2;
	t_vec			tmp3;
	t_vec			tmp4;
	t_vec			tmp5;

	initvec(0, 0, 1, &var->cam.up);
	var->cam.right = prodvec(&var->cam.up, &var->cam.dir);
	var->cam.up = prodvec(&var->cam.right, &var->cam.dir);
	normvec(&var->cam.right);
	normvec(&var->cam.up);
	normvec(&var->cam.dir);
	tmp = lenvec(var->cam.up, HEIGHT / -2);
	tmp2 = lenvec(var->cam.right, WIDTH / -2);
	tmp3 = addvec(tmp, tmp2);
	tmp5 = lenvec(var->cam.dir, DIST);
	tmp4 = addvec(tmp3, tmp5);
	var->viewplane.pos = addvec3d(var->cam.pos, tmp4);
}

void		resetcolor(t_var *var)
{
	var->colorf.r = 0;
	var->colorf.g = 0;
	var->colorf.b = 0;
}
