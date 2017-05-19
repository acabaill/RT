/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:38:57 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/17 16:57:14 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		get_dir(t_cut *cur, t_vec *pt)
{
	return ((((cur->dir.x * (pt->x - cur->pos.x)
		+ cur->dir.y * (pt->y - cur->pos.y)
		+ cur->dir.z * (pt->z - cur->pos.z))
		/ (cur->dir.x * cur->dir.x + cur->dir.y * cur->dir.y
		+ cur->dir.z * cur->dir.z)) * -1) > 0);
}

static double	lm(t_var *var, double x, t_obj *cur, double t1)
{
	t_vec	pt;
	int 	dir;

	if (x < 0.0001 || (t1 && x > t1))
		return (0);
	pt = addvec3d(var->cam.pos, lenvec(var->ray, x));
	dir = get_dir(&cur->cut, &pt);
	if (dir && cur->cut.t > x)
		return (0);
	return (x);
}

double			cut(t_var *var, t_equ *equ, t_obj *cur, double t1)
{
	double	min;


	cur->cut.t = ((cur->cut.dir.x * (var->cam.pos.x - cur->cut.pos.x)
		+ cur->cut.dir.y * (var->cam.pos.y - cur->cut.pos.y)
		+ cur->cut.dir.z * (var->cam.pos.z - cur->cut.pos.z))
		/ (cur->cut.dir.x * var->ray.x + cur->cut.dir.y * var->ray.y
		+ cur->cut.dir.z * var->ray.z)) * -1;
	if (!cur->cut_check)
		return (minus(equ->x1, equ->x2));
	if ((min = lm(var, (equ->x1 < equ->x2) ? equ->x1 : equ->x2, cur, t1)))
		return (min);
	min = lm(var, (equ->x1 > equ->x2) ? equ->x1 : equ->x2, cur, t1);
	return (min);
}
