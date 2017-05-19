/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 08:39:46 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 21:40:46 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void solve(t_vec *pt, t_vec *ray, t_obj *cur, t_equ *equ)
{
	ezvec(&cur->pos, pt, &cur->tool.vec1);
	equ->a = 1 - (1 + ft_sq(cur->tool.k)) * ft_sq(scal(ray, &cur->dir));
	equ->b = 2 * (scal(ray, &cur->tool.vec1) - (1 + ft_sq(cur->tool.k))
				* scal(ray, &cur->dir) * scal(&cur->tool.vec1, &cur->dir));
	equ->c = scal(&cur->tool.vec1, &cur->tool.vec1) - (1 + ft_sq(cur->tool.k))
	* ft_sq(scal(&cur->tool.vec1, &cur->dir));
	equ->d = ft_sq(equ->b) - (4 * equ->a * equ->c);
}

void	get_normal_cone(t_var *var, t_obj *cur, t_vec *pt)
{
	if (var)
	;
    cur->tool.n.x = pt->x - cur->pos.x
    - (1 + cur->tool.k * cur->tool.k) * cur->dir.x * cur->tool.coef;
    cur->tool.n.y = pt->y - cur->pos.y
    - (1 + cur->tool.k * cur->tool.k) * cur->dir.y * cur->tool.coef;
    cur->tool.n.z = pt->z - cur->pos.z
    - (1 + cur->tool.k * cur->tool.k) * cur->dir.z * cur->tool.coef;
    if (cur->state == 1 || cur->neg == -1)
    	rev_vec(&cur->tool.n);
}

void				ft_checkcone(t_var *var)
{
	t_equ	equ;
	double	t;
	double	u;
	double	v;
	t_obj 	*cur;

	cur = &var->obj[var->i];
	solve(&var->cam.pos, &var->ray, cur, &equ);
	if (equ.d < 0)
		return ;
	equ.x1 = ((equ.b * -1) - sqrt(equ.d)) / (2 * equ.a);
	equ.x2 = ((equ.b * -1) + sqrt(equ.d)) / (2 * equ.a);
	v = cut(var, &equ, cur, var->inter[0].t1);
	t = limit(var, &equ, cur, var->inter[0].t1);
	u = minus(t, v);
	if (u)
	{
		cur->tool.coef = scal(&var->ray, &cur->dir) * u
					+ scal(&cur->tool.vec1, &cur->dir);
		var->pt = addvec3d(var->cam.pos, lenvec(var->ray, u));
		var->tab4[cur->type](var, cur, &var->pt);
		if (u == equ.x2 && equ.x1 > 0.0001)
			rev_vec(&cur->tool.n);
		sort_inter(var, u, 0);
	}
}

int				ft_checkcone2(t_var *var, double d)
{
	t_equ	equ;
	double	t;

	t = 0;
	solve(&var->pt, &var->ray, &var->obj[var->i], &equ);
	if (equ.d < 0)
		return (0);
	equ.x1 = ((equ.b * -1) - sqrt(equ.d)) / (2 * equ.a);
	equ.x2 = ((equ.b * -1) + sqrt(equ.d)) / (2 * equ.a);
	if (var->obj[var->i].color.a == 1)
		if ((t = cut(var, &equ,
				&var->obj[var->i], var->inter_light[0].t1)))
			sort_inter_light(var, t, 0);
	if ((t > 0 && t < d))
		return (1);
	return (0);
}
