/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rfract_rflect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 14:41:08 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/12 18:19:06 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ez_reset(t_var *var)
{
	var->inter[0].t1 = 0;
	var->inter[0].t2 = 0;
	var->inter[0].obj = 0;
	var->inter[1].t1 = 0;
	var->inter[1].t2 = 0;
	var->inter[1].obj = 0;
}

void		uprayreflect(t_var *var, t_vec *n)
{
	var->ray = sousvec(var->raytmp, lenvec(*n, 2.0 * scal(&var->raytmp, n)));
	normvec(&var->ray);
	var->cam.pos = var->pt;
	var->coefreflect *= var->aliasreflect;
}

void		upraytrans(t_var *var, t_vec *n, t_obj *cur)
{
	double	n1;
	double	n2;
	double	scal1;

	var->cam.pos = var->pt;
	var->coefreflect *= (1.0 - var->aliasreflect);
	if ((cur->type == 1 || cur->type == 4))
	{
		var->ray = var->raytmp;
		return;
	}
	n1 = var->coef.n1;
	n2 = var->coef.n2;
	scal1 = scal(&var->raytmp, &cur->tool.n);
	var->ray.x = (n1 * (var->raytmp.x - n->x * scal1) / n2)
				- n->x * sqrt(1 - ((ft_sq(n->x)
					* (1 - ft_sq(scal1))) / ft_sq(n2)));
	var->ray.y = (n1 * (var->raytmp.y - n->y * scal1) / n2)
				- n->y * sqrt(1 - ((ft_sq(n->y)
					* (1 - ft_sq(scal1))) / ft_sq(n2)));
	var->ray.z = (n1 * (var->raytmp.z - n->z * scal1) / n2)
				- n->z * sqrt(1 - ((ft_sq(n->z)
					* (1 - ft_sq(scal1))) / ft_sq(n2)));
	normvec(&var->ray);
}
