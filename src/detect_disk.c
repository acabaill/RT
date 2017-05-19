/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_disk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 19:27:40 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/19 16:44:34 by acabaill         ###   ########.fr       */
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

void		ft_checkdisk(t_var *var)
{
	t_equ	equ;
	t_vec   pt;
 	t_vec   pt2;

	equ.x1 = solve(&var->cam.pos, &var->ray, &var->obj[var->i]);
 	pt = addvec3d(var->cam.pos, lenvec(var->ray, equ.x1));
	ezvec(&pt, &var->obj[var->i].pos, &pt2);
  if(sqrt(ft_sq(pt2.x) + ft_sq(pt2.y) + ft_sq(pt2.z)) > var->obj[var->i].r)
    return ;
	if (sort_inter(var, solve(&var->cam.pos, &var->ray, &var->obj[var->i]), 0))
		get_normal_plan(var, &var->obj[var->i], &var->pt);
}

int		ft_checkdisk2(t_var *var, double d)
{
	double	t;
	t_vec 	pt2;

	t = solve(&var->pt, &var->ray, &var->obj[var->i]);
	pt2 = addvec3d(var->cam.pos, lenvec(var->ray, t));
	ezvec(&pt2, &var->obj[var->i].pos, &pt2);
	if(sqrt(ft_sq(pt2.x) + ft_sq(pt2.y) + ft_sq(pt2.z) > var->obj[var->i].r))
	   return(0) ;
	if (var->obj[var->i].color.a == 1 && var->obj[var->i].neg != -1)
			sort_inter_light(var, t, 0);
	if ((t > 0 && t< d))
		return (1);
	return (0);
}
