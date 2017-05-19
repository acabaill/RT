/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:25:49 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 14:58:45 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		reset_y_alias(t_var *var)
{
	var->cam.pos = var->cam.tmpcam;
	var->coefreflect = var->coefreflect_alias;
	initray(var);
	var->raytmp = var->ray;
	var->objtmp = 0;
	var->gstate = -1;
	return (1);
}

static int		load(t_var *var)
{
	char *s;

	if((var->imgy % (var->sizey / 10)) == 0)
	{
		s = ft_itoa(var->nbi);
		var->surf = SDL_LoadBMP(s);
		free(s);
		var->nbi++;
		SDL_DestroyTexture(var->sdl_tex);
		var->sdl_tex = SDL_CreateTextureFromSurface(var->sdl_ren, var->surf);
		SDL_RenderClear(var->sdl_ren);
		SDL_RenderCopy(var->sdl_ren, var->sdl_tex, 0, 0);
		SDL_RenderPresent(var->sdl_ren);
		SDL_FreeSurface(var->surf);
	}
	return (1);
}

void		init_main_rt(t_var *var)
{
	ft_putendl("Init_main_rt");
	printf("Aliasing %d\n", var->aliasing);
	while ((load(var)) && (var->imgy < var->sizey || var->imgx < var->sizex))
	{
		var->imgx = 0;
		while (var->imgx < var->sizex && !(var->y_alias = 0))
		{
			while (var->y_alias < 1 && !(var->x_alias = 0))
			{
				while (var->x_alias < 1 && reset_y_alias(var))
				{
					var->curreflect = 0;
					var->curdepth = 0;
					main_rt(var);
					var->x_alias += var->off_alias;
				}
				var->y_alias += var->off_alias;
			}
			ft_pixel_put(var, 1);
			var->imgx++;
			resetcolor(var);
		}
		var->imgy++;
	}
}
