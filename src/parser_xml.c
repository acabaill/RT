/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_xml.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 19:06:58 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 17:28:36 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char *str_clean(char *c)
{
	int		i;
	char	*s;

	i = 0;
	while (*c && *c++ !='"')
		;
	while (c[i] != '"')
		i++;
	if (!(s = ft_strnew(i)))
		return (0);
	i = -1;
	while (c[++i] != '"')
		s[i] = c[i];
	s[i] = 0;
	return (s);
}

void 				new_texture(t_var *var, int fd)
{
	char	*s;
	char 	*tmp;
	static int i;

	s = 0;
	ft_putendl("Parsing CAM");
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/texture")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		if (ft_strstr(s, "new"))
		{
			s = str_clean(s);
			ft_putendl(s);
			var->text[i++] = SDL_LoadBMP(s);
			free(s);
		}
		free(tmp);
	}
	free(s);
}

static void			new_cam(t_var *var, int fd)
{
	t_vec	pos2;
	char	*s;
	char 	*tmp;

	s = 0;
	ft_putendl("Parsing CAM");
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/camera")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		if (ft_strstr(s, "pos1"))
			get_vec(s, &var->cam.pos);
		if (ft_strstr(s, "pos2"))
			get_vec(s, &pos2);
		ezvec(&var->cam.pos, &pos2, &var->cam.dir);
		free(tmp);
	}
	free(s);
}

static void parser_tag(t_var *var, char *s, int fd)
{
	if (ft_strstr(s, "camera"))
		new_cam(var, fd);
	if (ft_strstr(s, "light"))
		new_light(var, fd, &var->light[var->nblight]);
	if (ft_strstr(s, "object"))
		new_obj(var, fd, &var->obj[var->nbobj]);
	if (ft_strstr(s, "ambiant"))
		new_ambiant(var, fd);
	if (ft_strstr(s, "config"))
		new_config(var, fd);
	else if (ft_strstr(s, "texture"))
		new_texture(var, fd);
}

static int 		open_fd(t_var *var, char **av, int *fd)
{
	if (var)
		;
	preload(var);
	if (!(*fd = open(av[1], O_RDONLY)) || ft_check_xml(*fd, NULL) == -1)
		return (0);
	close(*fd);
	if (!(*fd = open(av[1], O_RDONLY)))
		return (0);
	return (1);
}

int				parser_xml(t_var *var, int ac, char **av)
{
	char	*s;
	char 	*tmp;
	int		fd;

	if (!open_fd(var, av, &fd))
		return (0);
	while (get_next_line(fd, &s))
	{
		tmp = s;
		ft_putendl(s);
		while (*s && *s++ != '<')
			;
		if (*s == '/')
		{
			free(tmp);
			continue ;
		}
		parser_tag(var, s, fd);
		free(tmp);
	}
	free(s);
	return (ac - ac + 1);
}
