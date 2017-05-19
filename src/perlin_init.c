/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 11:11:55 by pmartin           #+#    #+#             */
/*   Updated: 2016/09/14 11:12:04 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

void	init3(t_grid *grid)
{
	grid->grad[8][0] = 0;
	grid->grad[8][1] = 1;
	grid->grad[8][2] = 1;
	grid->grad[9][0] = 0;
	grid->grad[9][1] = -1;
	grid->grad[9][2] = 1;
	grid->grad[10][0] = 0;
	grid->grad[10][1] = 1;
	grid->grad[10][2] = -1;
	grid->grad[11][0] = 0;
	grid->grad[11][1] = -1;
	grid->grad[11][2] = -1;
	grid->grad[12][0] = 1;
	grid->grad[12][1] = 1;
	grid->grad[12][2] = 0;
	grid->grad[13][0] = -1;
	grid->grad[13][1] = 1;
	grid->grad[13][2] = 0;
	grid->grad[14][0] = 0;
	grid->grad[14][1] = -1;
	grid->grad[14][2] = 1;
	grid->grad[15][0] = 0;
	grid->grad[15][1] = -1;
	grid->grad[15][2] = -1;
}

void	init2(t_grid *grid)
{
	grid->grad[0][0] = 1;
	grid->grad[0][1] = 1;
	grid->grad[0][2] = 0;
	grid->grad[1][0] = -1;
	grid->grad[1][1] = 1;
	grid->grad[1][2] = 0;
	grid->grad[2][0] = 1;
	grid->grad[2][1] = -1;
	grid->grad[2][2] = 0;
	grid->grad[3][0] = -1;
	grid->grad[3][1] = -1;
	grid->grad[3][2] = 0;
	grid->grad[4][0] = 1;
	grid->grad[4][1] = 0;
	grid->grad[4][2] = 1;
	grid->grad[5][0] = -1;
	grid->grad[5][1] = 0;
	grid->grad[5][2] = 1;
	grid->grad[6][0] = 1;
	grid->grad[6][1] = 0;
	grid->grad[6][2] = -1;
	grid->grad[7][0] = -1;
	grid->grad[7][1] = 0;
	grid->grad[7][2] = -1;
}

double	fake_random(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return (1.0 - (t & 0x7fffffff) / 1073741824.0);
}

void	init(t_grid *grid)
{
	int		i;
	int		o;
	char	s[256];
	int		k;

	o = 0;
	i = 0;
	while (i < 256)
		s[i++] = 0;
	i = 0;
	while (i < 256)
	{
		k = (fake_random(o++) + 1) * 128;
		if (!s[k] && (s[k] = 1))
			grid->perm[i++] = (k == 0) ? 0 : k;
	}
	while (i < 512)
	{
		grid->perm[i] = grid->perm[i & 0xff];
		i++;
	}
	init2(grid);
	init3(grid);
	grid->o = 1;
}