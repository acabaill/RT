/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 20:30:46 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/11 18:40:36 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		get_coef_n_1_2(t_var *var, t_obj *cur)
{
	double tmp;

	tmp = var->coef.n2;
	if (var->gstate == cur->gradobj)
		var->coef.n2 = 1;
	else
		var->coef.n2 = cur->mat.n;
	if (var->gstate == -1)
	{
		var->coef.n1 = 1;
		var->gstate = cur->gradobj;
	}
	else
		var->coef.n1 = tmp;


}

void			coef_fresnel(t_var *var, t_obj *cur)
{
	double	r0;
	double	scal1;

	if (cur->type != 1 && cur->type != 4)
	get_coef_n_1_2(var, cur);
	scal1 = scal(&var->raytmp, &cur->tool.n);
	r0 = ft_sq((var->coef.n1 - var->coef.n2)
		/ (var->coef.n1 + var->coef.n2));
	var->aliasreflect = r0 + pow((1 - r0) * (1 - scal1), 5);
	var->aliasreflect = cur->color.a;
}
