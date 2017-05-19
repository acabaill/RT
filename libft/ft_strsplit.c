/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 11:42:10 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 12:27:25 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		count_words(const char *s, char c)
{
	int		cnt;
	int		tmp;

	tmp = 0;
	cnt = 0;
	while (*s)
	{
		if (tmp && *s == c)
			tmp = 0;
		if (!tmp && *s != c)
		{
			tmp = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		count_letter(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		nb_word;
	int		index;

	index = 0;
	nb_word = count_words((const char *)s, c);
	t = (char **)malloc(sizeof(*t) * (count_words((const char *)s, c) + 1));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s)
			s++;
		t[index] = ft_strsub((const char *)s, 0,
			count_letter((const char *)s, c));
		if (t[index] == NULL)
			return (NULL);
		s = s + count_letter(s, c);
		index++;
	}
	t[index] = NULL;
	return (t);
}
