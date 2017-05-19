/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 11:12:15 by pmartin           #+#    #+#             */
/*   Updated: 2016/09/14 13:03:53 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

double inter_li(double a, double b, double t)
{
	return ((1.0 - t) * a + t * b);
}

double	poly(double k)
{
	return (k * k * k * (k * (k * 6.0 - 15.0) + 10.0));
}

void	int_double(double k, t_double *doub)
{
	doub->inte = (__int64_t)k;
	if (k < 0)
		doub->inte--;
	doub->doub = k - doub->inte;
	doub->inte &= 0xff;
}

int *grad(t_grid *grid, int x, int y, int z)
{
	return (grid->grad[grid->perm[z + grid->perm[y + grid->perm[x]]] & 0xf]);
}

double	dot_product(int *grad, double x, double y, double z)
{
	return (grad[0] * x + grad[1] * y + grad[2] * z);
}
