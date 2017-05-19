/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 15:21:07 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/12 13:54:01 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		initvar(t_var *var)
{
	var->tab[0] = &ft_checksphere;
	var->tab[1] = &ft_checkplan;
	var->tab[2] = &ft_checkcone;
	var->tab[3] = &ft_checkcylinder;
	var->tab[4] = &ft_checkdisk;
	var->tab[5] = &ft_checkparaboloid;
	var->tab[6] = &ft_checktest;
	var->tab2[0] = &ft_checksphere2;
	var->tab2[1] = &ft_checkplan2;
	var->tab2[2] = &ft_checkcone2;
	var->tab2[3] = &ft_checkcylinder2;
	var->tab2[4] = &ft_checkdisk2;
	var->tab2[5] = &ft_checkparaboloid2;
	var->tab2[6] = &ft_checktest2;
	var->tab4[0] = &get_normal_sphere;
	var->tab4[1] = &get_normal_plan;
	var->tab4[2] = &get_normal_cone;
	var->tab4[3] = &get_normal_cylinder;
	var->tab4[4] = &get_normal_plan;
	var->tab4[5] = &get_normal_paraboloid;
	var->tab4[6] = &get_normal_test;
	initvar2(var);
}

void		initvar2(t_var *var)
{
	var->sizex = 1416;
	var->sizey = 1000;
	var->x_alias = 0;
	var->y_alias = 0;
	var->nblight = 0;
	var->nbobj = 0;
	var->cam.pos.x = 322;
	var->imgy = 0;
	var->imgx = 0;
	var->ray.x = 0;
	var->ray.y = 0;
	var->ray.z = 0;
	var->colorf.r = 0;
	var->colorf.g = 0;
	var->colorf.b = 0;
	var->reflect = 1;
	var->depth = 1;
	var->aliasing = 1;
	var->imgy = 0;
	var->nbi = 0;
}

void	init_calc(t_var *var)
{
	var->off_alias = 1.0 / var->aliasing;
	var->coefreflect_alias = 1.0 / ft_sq(var->aliasing);
	initviewplane(var);
	var->cam.tmpcam = var->cam.pos;
}
