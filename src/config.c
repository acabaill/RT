/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:32:53 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 15:00:12 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void config_tag(t_var *var, char *s)
{
	int nb;

	nb = 0;
	if (ft_strstr(s, "antialiasing"))
		var->aliasing = get_c(s, 'g');
	else if (ft_strstr(s, "filter"))
		var->filter = get_c(s, 'r');
	else if (ft_strstr(s, "reflect"))
		var->reflect = ((nb = get_c(s, 't')) > 1) ? nb : 1;
	else if (ft_strstr(s, "depth"))
		var->depth = ((nb = get_c(s, 'h')) > 1) ? nb : 1;
	else if (ft_strstr(s, "width"))
		var->sizex = get_c(s, 'w');
	else if (ft_strstr(s, "height"))
		var->sizey = get_c(s, 'h');
}

void			new_config(t_var *var, int fd)
{
	char	*s;
	char	*tmp;

	ft_putendl("NEW OBJ");
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/config")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		config_tag(var, s);
		free(tmp);
	}
	free(s);
	return ;
}
