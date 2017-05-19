/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 12:50:53 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/19 18:50:39 by acabaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void new_cut(int fd, t_cut *cur)
{
	char *s;
	char *tmp;

	while (get_next_line(fd, &s) && !(ft_strstr(s, "/cut")))
	{
		tmp = s;
		if (ft_strstr(s, "pos"))
			get_vec(s, &cur->pos);
		if (ft_strstr(s, "dir"))
			get_vec(s, &cur->dir);
		if (ft_strstr(s, "h1"))
			cur->h1 = get_c(s, '1');
		if (ft_strstr(s, "h2"))
			cur->h2 = get_c(s, '2');
		free(tmp);
	}
	normvec(&cur->dir);
	free(s);
}

static void 	new_obj_tag(t_var *var, int fd, t_obj *cur, char *s)
{
	if (ft_strstr(s, "type") && get_type(cur, s))
		var->nbobj++;
	else if (ft_strstr(s, "pos"))
		(ft_strstr(s, "pos2")) ? get_vec(s, &cur->pos2)
			: get_vec(s, &cur->pos);
	else if (ft_strstr(s, "dir"))
		get_vec(s, &cur->dir);
	else if (ft_strstr(s, "color"))
		cur->color = get_color(s);
	else if (ft_strstr(s, "radius"))
		cur->r = get_cf(s, 'r');
	else if (ft_strstr(s, "negative"))
		cur->neg = get_cf(s, 'v');
	else if (ft_strstr(s, "cut_check"))
		cur->cut_check = get_c(s, 't');
	else if (ft_strstr(s, "cut>"))
		new_cut(fd, &cur->cut);
	else if (ft_strstr(s, "mat>"))
		cur->mat = new_mat(fd);
	else if (ft_strstr(s, "texture"))
		cur->text = get_c(s, 't');
}


void			new_obj(t_var *var, int fd, t_obj *cur)
{
	char	*s;
	char	*tmp;

	s = 0;
	cur->gradobj = var->nbobj;
	cur->mat = var->defaultmat;
	cur->state = 0;
	cur->text = 0;
	cur->cut.h1 = 0;
	cur->cut.h2 = 0;
	ft_putendl("NEW OBJ");
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/object")))
	{
		tmp = s;
		ft_putendl(s);
		while (*s && *s++ != '<')
			;
		new_obj_tag(var, fd, cur, s);
		free(tmp);
	}
	normvec(&cur->dir);
	if (cur->type == 2)
		cur->tool.k = tan(3.1415 * (cur->r / 360.0));
	printf("CUT CHECK %d\n", cur->cut_check);
	free(s);
}
