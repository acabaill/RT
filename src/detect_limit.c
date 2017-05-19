/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:38:57 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/17 17:34:43 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	lm(t_var *var, double x, t_obj *cur, double t1)
{
	double	min_h;
	double	max_h;

	min_h = d_min(cur->cut.h1, cur->cut.h2);
	max_h = d_max(cur->cut.h1, cur->cut.h2);
	if (x < 0.0001 || (t1 && x > t1))
		return (0);
	cur->tool.coef = scal(&var->ray, &cur->dir) * x
					+ scal(&cur->tool.vec1, &cur->dir);
	if (min_h > cur->tool.coef || max_h < cur->tool.coef)
		return (0);
	return (x);
}

double			limit(t_var *var, t_equ *equ, t_obj *cur, double t1)
{
	double	min;

	if (cur->cut.h1 == cur->cut.h2)
		return (minus(equ->x1, equ->x2));
	if ((min = lm(var, (equ->x1 < equ->x2) ? equ->x1 : equ->x2, cur, t1)))
		return (min);
	else if ((min = lm(var, (equ->x1 > equ->x2) ? equ->x1 : equ->x2, cur, t1)))
		return (min);
	return (0);
}
