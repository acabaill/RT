/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 17:13:04 by pmartin           #+#    #+#             */
/*   Updated: 2017/04/30 17:11:37 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_cf(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
	{
		while (s[i] && s[i] != '"')
			i++;
		return (atof(&s[i + 1]));
	}
	return (0);
}

int			get_c(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
	{
		while (s[i] && s[i] != '"')
			i++;
		return (atoi(&s[i + 1]));
	}
	return (0);
}

t_color		get_color(char *s)
{
	t_color color;

	color.r = (double)get_c(s, 'r') / 255.0;
	color.g = (double)get_c(s, 'g') / 255.0;
	color.b = (double)get_c(s, 'b') / 255.0;
	color.a = (double)get_c(s, 'a') / 255.0;
	return (color);
}
