
#include "rtv1.h"

static void new_light_tag(t_light *cur, char *s, double *lum)
{
	if (ft_strstr(s, "pos"))
		get_vec(s, &cur->pos);
	if (ft_strstr(s, "color"))
		cur->color = get_color(s);
	if (ft_strstr(s, "lum"))
		*lum = get_c(s, 'm');
}


void		new_light(t_var *var, int fd, t_light *cur)
{
	char	*s;
	char 	*tmp;
	double	lum;

	s = 0;
	ft_putendl("Parsing Light");
	var->nblight++;
	lum = 0;
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/light")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		new_light_tag(cur, s, &lum);
		free(tmp);
	}
	free(s);
	if (lum)
	{
		lum = lum/ 100.0;
		cur->color.r *= lum;
		cur->color.g *= lum;
		cur->color.b *= lum;
	}
}

void		new_ambiant(t_var *var, int fd)
{
	char	*s;
	char 	*tmp;

	s = 0;
	ft_putendl("Parsing Ambiant");
	while (get_next_line(fd, &s) && !(ft_strstr(s, "/ambiant")))
	{
		tmp = s;
		while (*s && *s++ != '<')
			;
		if (ft_strstr(s, "color"))
			var->ambiant.color = get_color(s);
		free(tmp);
	}
	free(s);
}
