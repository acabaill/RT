/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 18:54:49 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/03 20:19:07 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		preload(t_var *var)
{
	int fd;

	if (!(fd = open("default/mat.xml", O_RDONLY)))
	{
		ft_putendl("No default mat");
		return ;
	}
	var->defaultmat = new_mat(fd);
	close(fd);
	var->ambiant.color.r = 1;
	var->ambiant.color.g = 1;
	var->ambiant.color.b = 1;
}
