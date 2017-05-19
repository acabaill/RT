/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 21:44:37 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/16 18:46:01 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void event_sdl(t_var *var)
{
	while (1)
	{
		SDL_WaitEvent(&var->event);
		if (/*var->event.window.event == SDL_WINDOWEVENT_CLOSE
			|| */var->event.type == SDL_QUIT
			|| var->event.key.keysym.sym == SDLK_ESCAPE)
			break ;
		else if(var->event.key.keysym.sym == SDLK_p)
			SDL_SaveBMP(var->surface, "Image.bmp");
		else if (var->event.key.keysym.sym == SDLK_r)
		{
			SDL_DestroyTexture(var->sdl_tex);
			var->sdl_tex = SDL_CreateTextureFromSurface(var->sdl_ren, var->surface);
			SDL_RenderClear(var->sdl_ren);
			SDL_RenderCopy(var->sdl_ren, var->sdl_tex, 0, 0);
			SDL_RenderPresent(var->sdl_ren);
		}
	}
	SDL_DestroyTexture(var->sdl_tex);
	SDL_DestroyWindow(var->sdl_win);
	SDL_Quit();
}

static void printf_obj(t_var *var)
{
	int i = -1;

	ft_putendl("CAM:");
	ft_printvec(&var->cam.pos, "POS");
	ft_printvec(&var->cam.dir, "DIR");
	printf("Reflect %d, Trans %d\n", var->reflect, var->depth);
	while (++i < var->nbobj)
	{
		ft_putendl("NEWOBJJJJJJ::::");
		printf("Type :: %d Gradobj :: %d\n", var->obj[i].type, var->obj[i].gradobj);
		ft_printvec(&var->obj[i].pos, "POS");
		ft_printvec(&var->obj[i].dir, "DIR");
		printf("R %g G %g B %g A %g\n", var->obj[i].color.r, var->obj[i].color.g, var->obj[i].color.b, var->obj[i].color.a);
		printf("n == %g\n", var->obj[i].mat.n);
		printf("cut h1:%g H2:%g\n", var->obj[i].cut.h1, var->obj[i].cut.h2);
	}
}

int			main(int ac, char **av)
{
	t_var	var;

	if (ac != 2)
		return (-1);
	initvar(&var);
	ft_putendl("Init Ok");
	if (av)
		;
	if (!parser_xml(&var, ac, av))
		return (-1);
	printf_obj(&var);
	ft_putendl("Parser Ok");
	if (SDL_Init(SDL_INIT_VIDEO))
		return (-1);
	var.sdl_win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED,
								   var.sizex, var.sizey,
								   SDL_WINDOW_SHOWN);
	var.sdl_ren = SDL_CreateRenderer(var.sdl_win, -1,
		 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(var.sdl_ren, 0x00, 0x00, 0x00, 0x00);
	var.surface = SDL_CreateRGBSurface(0, var.sizex, var.sizey, 32,
									   0, 0, 0, 0);
	init_calc(&var);
	var.sdl_tex = SDL_CreateTextureFromSurface(var.sdl_ren, var.surface);
	init_main_rt(&var);
	event_sdl(&var);
	return (0);
}
