/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoutinh <mcoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:38:14 by mcoutinh          #+#    #+#             */
/*   Updated: 2017/05/03 16:07:13 by mcoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

/* DEFINE FT UTILITIES */

static char		*ft_sjoin_del(char *s1, char *s2)
{
	char		*new;
	int			i;
	int			j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	if ((new = (char *)malloc(sizeof(*new) * (i + j + 1))) == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (new);
}

static char		*ft_cjoin_del(char *s, char c)
{
	char		*new;
	int			i;

	i = 0;
	while (s[i])
		i++;
	if ((new = (char *)malloc(sizeof(*new) * i + 2)) == NULL)
		return (NULL);
	new[i + 1] = '\0';
	new[i] = c;
	i = -1;
	while (s[++i])
		new[i] = s[i];
	ft_strdel(&s);
	return (new);
}

/* ENDIF FT UTILITIES */

static int		ft_ignore_tag_content(t_checker *c, char **tofree)
{
	char		dquote;
	char		quote;

	ft_strdel(tofree);
	dquote = 'n';
	quote = 'n';
	while ((c->file[++(c->i)] && c->file[c->i] != '>')
			|| dquote == 'y' || quote == 'y')
	{
		if (c->file[c->i] == '\"' && quote == 'n')
		{
			if (dquote == 'n' && c->file[c->i - 1] != '=')
				return (ft_putstr_fd("Error: attribute syntax incorrect\n", 2));
			dquote = (dquote == 'n' ? 'y' : 'n');
		}
		if (c->file[c->i] == '\'' && dquote == 'n')
		{
			if (quote == 'n' && c->file[c->i - 1] != '=')
				return (ft_putstr_fd("Error: attribute syntax incorrect\n", 2));
			quote = (quote == 'n' ? 'y' : 'n');
		}
	}
	if (c->file[c->i - 1] != '/')
		return (ft_putstr_fd("Error: tag syntax incorrect\n", 2));
	return (0);
}

static int		ft_create_tag(t_checker *c, char **name)
{
	t_tag		*new;
	t_tag		*tmp;

	if ((new = (t_tag *)malloc(sizeof(*new) * 1)) == NULL)
		return (ft_putstr_fd("Error: malloc() failed\n", 2));
	tmp = c->tags;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		c->tags = new;
	new->closer = ft_sjoin_del(ft_strdup("</"), ft_cjoin_del(*name, '>'));
	new->prev = tmp;
	new->next = NULL;
	return (0);
}

static int		ft_close_tag(t_checker *c)
{
	t_tag		*tmp;

	if ((tmp = c->tags) == NULL)
		return (ft_putstr_fd("Error: no tag to close\n", 2));
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (ft_strncmp(tmp->closer, c->file + c->i, ft_strlen(tmp->closer)) != 0)
		return (ft_putstr_fd("Error: unexpected close tag\n", 2));
	if (tmp->prev)
		tmp->prev->next = NULL;
	else
		c->tags = NULL;
	tmp->prev = NULL;
	ft_strdel(&(tmp->closer));
	free(tmp);
	tmp = NULL;
	return (0);
}

static int		ft_check_tag(t_checker *c)
{
	char		*name;

	if (!ft_isalpha(c->file[c->i + 1]))
		return (ft_putstr_fd("Error: tag's name invalid\n", 2));
	if ((name = ft_strnew(0)) == NULL)
		return (ft_putstr_fd("Error: ft_strnew() failed\n", 2));
	while (c->file[++(c->i)] && c->file[c->i] != ' ' && c->file[c->i] != '>')
	{
		if ((name = ft_cjoin_del(name, c->file[c->i])) == NULL)
			return (ft_putstr_fd("Error: ft_cjoin() failed\n", 2));
	}
	if (c->file[c->i] == ' ')
		return (ft_ignore_tag_content(c, &name));
	else if (c->file[c->i] == '>')
		return (ft_create_tag(c, &name));
	return (ft_putstr_fd("Error: undefined content\n", 2));
}

static int		ft_init_del_checker(t_checker *c, int opt)
{
	if (opt == 1)
	{
		c->tags = NULL;
		c->i = -1;
		if ((c->file = ft_strnew(0)) == NULL)
			return (ft_putstr_fd("Error: ft_strnew() failed\n", 2));
	}
	if (opt == 2)
	{
		ft_strdel(&(c->file));
		if (c->tags)
		{
			return (ft_putstr_fd("Error: some tags are not closed\n", 2));
		}
	}
	return (0);
}
int		ft_check_xml(int fd, char *line)
{
	t_checker	c;

	if (ft_init_del_checker(&c, 1) == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '<' && line[1] == '?'
				&& line[ft_strlen(line) - 2] == '?'
				&& line[ft_strlen(line) - 1] == '>')
			ft_strdel(&line);
		else if ((c.file = ft_sjoin_del(c.file, line)) == NULL)
			return (ft_putstr_fd("Error: ft_sjoin() failed\n", 2));
	}
	if ((c.file = ft_sjoin_del(c.file, line)) == NULL)
			return (ft_putstr_fd("Error: ft_sjoin() failed\n", 2));
	while (c.file[++(c.i)])
	{
		if (c.file[c.i] == '<')
		{
			if (c.file[c.i + 1] == '/')
				ft_close_tag(&c);
			else if (ft_check_tag(&c) == -1)
				return (-1);
		}
	}
	return (ft_init_del_checker(&c, 2));
}
