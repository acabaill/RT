/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:14:14 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/17 18:07:46 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	specular(t_var *var, t_light *light, t_obj *cur)
{
	if (cur->mat.coef)
	{
		cur->tool.vec2 = sousvec(var->ray, var->raytmp);
		cur->tool.tmp = sqrt(scal(&cur->tool.vec2, &cur->tool.vec2));
		if (cur->tool.tmp)
		{
			cur->tool.vec2 = lenvec(cur->tool.vec2, 1.0 / cur->tool.tmp);
			cur->tool.coef = scal(&cur->tool.vec2, &cur->tool.n);
			cur->tool.coef = cur->mat.coef * powf(cur->tool.coef, cur->mat.pow);
			if (cur->tool.coef > 0)
				makecolor2(var, cur->tool.coef * var->coefreflect
					, light);
		}
	}
}
