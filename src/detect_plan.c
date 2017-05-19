/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 19:27:40 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/16 17:32:04 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double solve(t_vec *pt, t_vec *ray, t_obj *cur)
{
	return (((cur->dir.x * (pt->x - cur->pos.x)
		+ cur->dir.y * (pt->y - cur->pos.y)
		+ cur->dir.z * (pt->z - cur->pos.z))
		/ (cur->dir.x * ray->x + cur->dir.y * ray->y
		+ cur->dir.z * ray->z)) * -1);
}

void	get_normal_plan(t_var *var, t_obj *cur, t_vec *pt)
{
	if (pt && var)
		;
    cur->tool.n = cur->dir;
}

void		ft_checkplan(t_var *var)
{
	if (sort_inter(var, solve(&var->cam.pos, &var->ray, &var->obj[var->i]), 0))
		get_normal_plan(var, &var->obj[var->i], &var->pt);
}

int		ft_checkplan2(t_var *var, double d)
{
	double	t;

	t = 0;
	t = solve(&var->pt, &var->ray, &var->obj[var->i]);
	if (var->obj[var->i].color.a == 1 && var->obj[var->i].neg != -1)
			sort_inter_light(var, t, 0);
	if ((t > 0 && t< d))
		return (1);
	return (0);
}
