/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 05:19:41 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/16 15:20:04 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void cell_shading(t_var *var, t_obj *cur, double *c)
{
 	if (-scal(&cur->tool.n, &var->raytmp) < 0.2)
		*c = 0;
	if (*c < 0.2)
        *c = 0;
    else if (*c >= 0.3 && *c < 0.6)
        *c = 0.3;
    else if (*c >= 0.6 && *c < 0.9)
        *c = 0.6;
    else if (*c >= 0.9)
        *c = 0.9;
}

static void		ft_light2(t_var *var, t_light *light, t_obj *cur)
{
	if (cur->mat.perlin & BUMP)
		get_n_perlined2(&cur->tool.n, &var->pt);
	normvec(&cur->tool.n);
	cur->tool.coef = scal(&cur->tool.n, &var->ray);
	if ((cur->type == 1 || cur->type == 4) && cur->tool.coef < 0)
	{
        rev_vec(&cur->tool.n);
		cur->tool.coef = scal(&cur->tool.n, &var->ray);
	}
	if (var->filter == 3)
		cell_shading(var, cur, &cur->tool.coef);
	cur->tool.coef *= var->coefreflect * cur->color.a  * var->coef_light;
	if (cur->mat.perlin & CHELOU)
		cur->tool.coef *= ezperlin(&var->pt);
	if (!var->checkshad)
	{
		makecolor(var, cur->tool.coef, cur, light);
		specular(var, light, cur);
	}
}

static void		detect(t_var *var, t_obj *cur, double d)
{
	while (++var->i < var->nbobj)
		if (cur != &var->obj[var->i] && var->obj[var->i].neg != -1
			&& var->tab2[var->obj[var->i].type](var, d)
			&& var->obj[var->i].color.a != 1)
				var->coef_light *= (1 - var->obj[var->i].color.a);
	if (var->inter_light[0].t1 > 0 && var->inter_light[0].t1 < d)
			var->checkshad = 1;
	var->inter_light[0].t1 = 0;
}

 void 	ambiant(t_var *var, t_obj *cur)
{
	makecolor(var, 0.1 * cur->color.a
		* var->coefreflect_alias, cur, &var->ambiant);
}

void			ft_light(t_var *var, t_obj *cur)
{
	int		i;
	double	d;

	i = 0;
	while (i < var->nblight)
	{
		var->i = -1;
		var->coef_light = 1;
		var->checkshad = 0;
		d = ft_dist(&var->pt, &var->light[i].pos);
		ezvec(&var->pt, &var->light[i].pos, &var->ray);
		normvec(&var->ray);
		detect(var, cur, d);
		normvec(&cur->tool.n);
		ft_light2(var, &var->light[i], cur);
		i++;
	}
	if (var->curreflect == 1 && var->curdepth == 1)
		ambiant(var, cur);
}
