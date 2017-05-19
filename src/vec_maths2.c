/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_maths2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:35:27 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/15 14:44:00 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		addvec3d(t_vec b, t_vec vec)
{
	b.x += vec.x;
	b.y += vec.y;
	b.z += vec.z;
	return (b);
}

t_vec		sousvec(t_vec a, t_vec b)
{
	t_vec x;

	x.x = a.x - b.x;
	x.y = a.y - b.y;
	x.z = a.z - b.z;
	return (x);
}

t_vec		prodvec(t_vec *u, t_vec *v)
{
	t_vec tmp;

	tmp.x = (u->y * v->z - u->z * v->y);
	tmp.y = (u->z * v->x - u->x * v->z);
	tmp.z = (u->x * v->y - u->y * v->x);
	return (tmp);
}

void		initvec(double x, double y, double z, t_vec *vec)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void rev_vec(t_vec *t)
{
	t->x *= -1;
	t->y *= -1;
	t->z *= -1;
}
