/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:58:44 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/12 12:13:33 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void solve(t_vec *pt, t_vec *ray, t_obj *cur, t_equ *equ)
{
	ezvec(&cur->pos, pt, &cur->tool.vec1);
	equ->a = 1 - ft_sq(scal(ray, &cur->dir));
	equ->b = (scal(ray, &cur->tool.vec1) - scal(ray, &cur->dir)
			* (scal(&cur->tool.vec1, &cur->dir) + 2 * cur->r)) * 2;
	equ->c = scal(&cur->tool.vec1, &cur->tool.vec1)
	- scal(&cur->tool.vec1, &cur->dir)
			* (scal(&cur->tool.vec1, &cur->dir) + 4 * cur->r);
	equ->d = ft_sq(equ->b) - (4 * equ->a * equ->c);
}

void	get_normal_test(t_var *var, t_obj *cur, t_vec *pt)
{
	cur->tool.coef = scal(&var->ray, &cur->dir)
	* ft_dist(&var->cam.pos, pt) + scal(&cur->tool.vec1, &cur->dir);
	cur->tool.n.x = pt->x - cur->pos.x - (cur->dir.x
		* (cur->tool.coef + cur->r));
	cur->tool.n.y = pt->y - cur->pos.y - (cur->dir.y
		* (cur->tool.coef + cur->r));
	cur->tool.n.z = pt->z - cur->pos.z - (cur->dir.z
		* (cur->tool.coef + cur->r));
	if (cur->state == 1 || cur->neg == -1)
	{
		cur->tool.n.x *= -1;
		cur->tool.n.y *= -1;
		cur->tool.n.z *= -1;
	}
}

void				ft_checktest(t_var *var)
{
	t_equ equ;

	solve(&var->cam.pos, &var->ray, &var->obj[var->i], &equ);
	if (equ.d < 0)
		return ;
	equ.x1 = ((equ.b * -1) - sqrt(equ.d)) / (2 * equ.a);
	equ.x2 = ((equ.b * -1) + sqrt(equ.d)) / (2 * equ.a);
	if (sort_inter(var, equ.x1, equ.x2))
	{
		var->pt = addvec3d(var->cam.pos, lenvec(var->ray
		,(var->inter[0].obj->neg == -1) ? var->inter[0].t2 : var->inter[0].t1));
		get_normal_test(var, &var->obj[var->i], &var->pt);
	}
}

int				ft_checktest2(t_var *var, double d)
{
	t_equ equ;

	solve(&var->pt, &var->ray, &var->obj[var->i], &equ);
	if (equ.d < 0)
		return (0);
	equ.x1 = ((equ.b * -1) - sqrt(equ.d)) / (2 * equ.a);
	equ.x2 = ((equ.b * -1) + sqrt(equ.d)) / (2 * equ.a);
	if (var->obj[var->i].color.a == 1 && var->obj[var->i].neg != -1)
		sort_inter_light(var, equ.x1, equ.x2);
	if ((equ.x1 > 0 && equ.x1 < d) || (equ.x2 > 0 && equ.x2 < d))
		return (1);
	return (0);
}
