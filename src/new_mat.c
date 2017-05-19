/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 17:21:23 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/03 20:18:15 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat		new_mat(int fd)
{
	char *s;
	t_mat mat;
	char *tmp;

	while (get_next_line(fd, &s) && !(ft_strstr(s, "/mat")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		if (ft_strstr(s, "perlin"))
			mat.perlin = get_c(s, 'n');
		if (ft_strstr(s, "color1") && s[5] != '2')
			mat.color1 = get_color(s);
		if (ft_strstr(s, "color2"))
			mat.color2 = get_color(s);
		if (ft_strstr(s, "coefspec"))
			mat.coef = get_cf(s, 'f');
		if (ft_strstr(s, "pow"))
			mat.pow = get_cf(s, 'c');
		if (ft_strstr(s, "n"))
			mat.n = get_cf(s, 'n');
		free(tmp);
	}
	free(s);
	return (mat);
}
