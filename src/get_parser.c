/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:32:34 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/03 16:55:59 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_vec(char *s, t_vec *vec)
{
	initvec(get_cf(s, 'x'), get_cf(s, 'y'),
			get_cf(s, 'z'), vec);
}

int				get_type(t_obj *cur, char *s)
{
	int i;

	i = 0;
	ft_putendl(s);
	while (s[i] && s[i] != '"')
		i++;
	if (s[i] && ft_strstr(s, "sphere"))
		cur->type = 0;
	else if (s[i] && ft_strstr(s, "plan"))
		cur->type = 1;
	else if (s[i] && ft_strstr(s, "cone"))
		cur->type = 2;
	else if (s[i] && ft_strstr(s, "cylinder"))
		cur->type = 3;
	else if (s[i] && ft_strstr(s, "disk"))
		cur->type = 4;
	else if (s[i] && ft_strstr(s, "paraboloid"))
		cur->type = 5;
	else
		return (0);
	return (1);
}
