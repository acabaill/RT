/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_main_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:25:01 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/14 18:35:33 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		reset_inter(t_var *var)
{
	var->inter[0].t1 = 0;
	var->inter[0].t2 = 0;
	var->inter[0].obj = 0;
	var->inter[1].t1 = 0;
	var->inter[1].t2 = 0;
	var->inter[1].obj = 0;
	var->inter_light[0].t1 = 0;
	var->inter_light[0].t2 = 0;
	var->inter_light[0].obj = 0;
	var->inter_light[1].t1 = 0;
	var->inter_light[1].t2 = 0;
	var->inter_light[1].obj = 0;
	var->i = -1;
	var->curreflect++;
	var->curdepth++;
	var->curobj = 0;
	var->raytmp = var->ray;
}

static int 		detect(t_var *var)
{
	while (++var->i < var->nbobj)
			var->tab[var->obj[var->i].type](var);
	if (!((var->inter[0].obj && var->inter[0].obj->neg == -1
		&& var->inter[1].obj && var->inter[0].t2 < 200000000)
		|| (var->inter[0].obj && var->inter[0].obj->neg != 1
		&& var->inter[0].t1 < 200000000)))
		return (0);
	if (var->inter[0].obj->neg == -1 && !var->inter[1].obj)
		return (0);
	return (1);
}

void		ezsave(t_var *var, t_save *save, t_obj *cur)
{
	int i;

	i = -1;
	save->o = var->cam.pos;
	save->raytmp = var->raytmp;
	save->objtmp = var->objtmp;
	save->tool = var->tool;
	save->coefreflect = var->coefreflect;
	save->aliasreflect = var->aliasreflect;
	save->n1 = var->coef.n1;
	save->n2 = var->coef.n2;
	save->gstate = var->gstate;
	while (++i < var->nbobj)
		save->tab[i] = var->obj[i].state;
	if (cur->type != 1)
	{
		if (cur->state == 1)
			var->gstate -= cur->gradobj;
		else
			var->gstate += cur->gradobj;
		if (cur->state == 1)
			cur->state = 0;
		else
			cur->state = 1;
	}
}

void		ezrestore(t_var *var, t_save *save)
{
	int i;

	i = -1;
	var->coefreflect = save->coefreflect;
	var->aliasreflect = save->aliasreflect;
	var->cam.pos = save->o;
	var->raytmp = save->raytmp;
	var->objtmp = save->objtmp;
	var->tool = save->tool;
	var->coef.n1 = save->n1;
	var->coef.n2 = save->n2;
	var->gstate = save->gstate;
	while (++i < var->nbobj)
		var->obj[i].state = save->tab[i];
}

void			main_rt(t_var *var)
{
	t_save	save;
	t_obj	*cur;

	//printf("Imgx %d, Imgy %d \n", var->imgx, var->imgy);
	reset_inter(var);
	if (!detect(var))
		return ;
	cur = (var->inter[0].obj->neg == -1) ? var->inter[1].obj
		: var->inter[0].obj;
	var->pt = addvec3d(var->cam.pos, lenvec(var->ray
		,(var->inter[0].obj->neg == -1) ? var->inter[0].t2 : var->inter[0].t1));
	ft_light(var, cur);
	coef_fresnel(var, cur);
	ezsave(var, &save, cur);
	upraytrans(var, &cur->tool.n, cur);
	if (var->coefreflect && cur->color.a != 1 && var->aliasreflect != 1
		&& var->curdepth < var->depth)
		main_rt(var);
	ezrestore(var, &save);
	uprayreflect(var, &cur->tool.n);
	if (var->coefreflect && var->aliasreflect && var->curreflect < var->reflect)
		main_rt(var);
}
