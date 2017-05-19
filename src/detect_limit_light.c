/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:38:57 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/16 14:13:17 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	lm_light(t_var *var, double x, t_obj *cur, double t1)
{
	double	min_h;
	double	max_h;

	min_h = d_min(cur->cut.h1, cur->cut.h2);
	max_h = d_max(cur->cut.h1, cur->cut.h2);
	if (x < 0.001 || (t1 && x > t1))
		return (0);
	cur->tool.coef = scal(&var->ray, &cur->dir) * x
					+ scal(&cur->tool.vec1, &cur->dir);
	if (min_h > cur->tool.coef || max_h < cur->tool.coef)
		return (0);
	return (x);
}

double			limit_light(t_var *var, t_equ *equ, t_obj *cur, double t1)
{
	double	min;

	if (cur->cut.h1 == cur->cut.h2)
		if ((min = minus(equ->x1, equ->x2)))
			return (min);
	if ((min = lm_light(var, (equ->x1 < equ->x2) ? equ->x1 : equ->x2, cur, t1)))
		return (min);
	else if ((min = lm_light(var,
			(equ->x1 > equ->x2) ? equ->x1 : equ->x2, cur, t1)))
			return (min);
	return (0);
}
