/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:23:20 by pmartin           #+#    #+#             */
/*   Updated: 2016/07/21 04:01:10 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		normvec(t_vec *vec)
{
	double	len;

	len = sqrt(ft_sq(vec->x) + ft_sq(vec->y) + ft_sq(vec->z));
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
	return (len);
}

void		ezvec(t_vec *a, t_vec *b, t_vec *vec)
{
	vec->x = b->x - a->x;
	vec->y = b->y - a->y;
	vec->z = b->z - a->z;
}

t_vec		addvec(t_vec a, t_vec b)
{
	t_vec tmp;

	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	tmp.z = a.z + b.z;
	return (tmp);
}

double		scal(t_vec *a, t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vec		lenvec(t_vec vec, double len)
{
	vec.x *= len;
	vec.y *= len;
	vec.z *= len;
	return (vec);
}
