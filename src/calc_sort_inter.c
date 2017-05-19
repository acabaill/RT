/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sort_inter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 23:12:51 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/17 18:16:25 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double 		d_max(double x, double y)
{
	return ((x > y) ? x : y);
}

double 		d_min(double x, double y)
{
	return ((x < y) ? x : y);
}

double	minus(double x, double y)
{
	if (x < 0.0001 && y > 0.0001)
		return (y);
	if (x > 0.0001 && y < 0.0001)
		return (x);
	if (x < 0.0001 && y < 0.0001)
		return (0);
	return (d_min(x, y));
}

int		sort_inter(t_var *var, double x1, double x2)
{
	if (((x1 < x2 || x2 <= 0.0001) && x1 > 0.0001
		&& (x1 < var->inter[0].t1 || !var->inter[0].t1)))
	{
		var->inter[0].t1 = x1;
		var->inter[0].t2 = x2;
		var->inter[0].obj = &var->obj[var->i];
		return (1);
	}
	else if ((x2 < x1 || x1 < 0.0001) && x2 > 0.0001
		&& (x2 < var->inter[0].t1 || !var->inter[0].t1))
	{
		var->inter[0].t1 = x2;
		var->inter[0].t2 = x1;
		var->inter[0].obj = &var->obj[var->i];
		return (1);
	}
	return (0);
}

void		sort_inter_light(t_var *var, double x1, double x2)
{
	if (((x1 < x2 || x2 <= 0.0001) && x1 > 0.0001
		&& (x1 < var->inter_light[0].t1 || !var->inter_light[0].t1)))
	{
		var->inter_light[0].t1 = x1;
		var->inter_light[0].t2 = x2;
		var->inter_light[0].obj = &var->obj[var->i];
	}
	else if ((x2 < x1 || x1 < 0.0001) && x2 > 0.0001
		&& (x2 < var->inter_light[0].t1 || !var->inter_light[0].t1))
	{
		var->inter_light[0].t1 = x2;
		var->inter_light[0].t2 = x1;
		var->inter_light[0].obj = &var->obj[var->i];
	}
}
