/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:19:49 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 21:22:26 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void get_map_sphere(double *x, double *y, t_obj *cur)
{
    t_vec       ve;
    t_vec       vn;
    double      theta;

    ve = (t_vec){0, 1, 0};
    vn = (t_vec){0, 0, -1};
    theta = acos(d_min(d_max(scal(&cur->tool.n, &ve)
            / sin(acos(-scal(&vn, &cur->tool.n))),-1.0),1.0)) / (1 * PI);
    *y = acos(-scal(&vn, &cur->tool.n)) / PI;
    ve = prodvec(&vn, &ve);
    if (scal(&ve, &cur->tool.n) > 0)
        *x = theta;
    else
        *x = 1 - theta;
}
//
// static void get_map_plan(double *x, double *y, t_obj *cur, t_var *var)
// {
//     *x = (var->pt.x - cur->pos.x) /
//         (cur->pos.y - cur->pos.x);
//     *y = (var->pt.y - cur->dir.x) /
//         (cur->dir.y - cur->dir.x);
//     // else
//     // {
//     //     map.x = fmod(abs_double(var->pt.x), (object->texture->width / 100.0)) /
//     //     (object->texture->width / 100.0);
//     //     map.y = fmod(abs_double(var->pt.y), (object->texture->height / 100.0)) /
//     //     (object->texture->height / 100.0);
//     // }
// }

static void get_color_text(t_obj *cur, t_var *var, t_color *colorf)
{
    int color;
    double x;
    double y;
    int     x2;
    int     y2;

    if (!var->text[cur->text - 1])
        return ;
    get_map_sphere(&x, &y, cur);
    // else
    //     get_map_plan(&x, &y, cur, var);
    x2 = x * var->text[cur->text - 1]->w;
    y2 = y * var->text[cur->text - 1]->h;
    ft_memcpy(&color, var->text[cur->text - 1]->pixels
        + y2 * var->text[cur->text - 1]->pitch + x2 * 3, 3);
    colorf->r = ((color >> 16) & 255) / 255.0;
    colorf->g = ((color >> 8) & 255) / 255.0;
    colorf->b = (color & 255) / 255.0;
}


void make_text(t_var *var, double coef, t_obj* cur, t_light *light)
{
    t_color colorf;

    get_color_text(cur, var, &colorf);
    var->colorf.r += coef * light->color.r * colorf.r;
    var->colorf.g += coef * light->color.g * colorf.g;
    var->colorf.b += coef * light->color.b * colorf.b;
}
