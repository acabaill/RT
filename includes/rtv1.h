/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 22:44:49 by pmartin           #+#    #+#             */
/*   Updated: 2017/05/18 16:31:22 by pmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define WIDTH 0.5
# define HEIGHT 0.35
# define DIST 1
# define CAST (double)
# define NBOBJ 60
# define NBLIGHT 40
# define NBTEXT 10
# define PI 3.14159265359
# include <SDL2/SDL.h>
# include "../libft/includes/libft.h"
# include "get_next_line.h"
# include "perlin.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>

typedef struct				s_vec
{
	double					x;
	double					y;
	double					z;
}							t_vec;
typedef struct				s_color
{
	double					r;
	double					g;
	double					b;
	double					a;
}							t_color;
typedef struct				s_cut
{
	double					h1;
	double					h2;
	t_vec					pos;
	t_vec					dir;
	int						cut;
	double					t;
}							t_cut;
typedef struct				s_mat
{
	double					pow;
	double					coef;
	double					n;
	int 					perlin;
	t_color					color1;
	t_color					color2;
}							t_mat;
typedef struct				s_equ
{
	double					a;
	double					b;
	double					c;
	double					d;
	double					x1;
	double					x2;
	double					k;
}							t_equ;
typedef struct				s_viewplane
{
	t_vec					pos;
	t_vec					v;
	double					x;
	double					y;
}							t_viewplane;
typedef struct				s_tool
{
	t_vec					n;
	t_vec					light;
	t_vec					vec1;
	t_vec					vec2;
	double					coef;
	double					k;
	double					tmp;
}							t_tool;
typedef struct				s_obj
{
	int						type;
	t_vec					pos;
	t_vec					pos2;
	t_vec					dir;
	double					r;
	double					r2;
	t_color					color;
	t_mat					mat;
	t_tool					tool;
	int						neg;
	int						state;
	int						gradobj;
	int						cut_check;
	t_cut					cut;
	int						text;
}							t_obj;
typedef struct				s_light
{
	t_vec					pos;
	t_color					color;
	double					tam;
}							t_light;
typedef struct				s_cam
{
	t_vec					pos;
	t_vec					tmpcam;
	t_vec					dir;
	t_vec					up;
	t_vec					right;
}							t_cam;
typedef struct				s_inter
{
	t_obj					*obj;
	double					t1;
	double					t2;
}							t_inter;
typedef struct				s_coef
{
	double					n1;
	double					n2;
}							t_coef;
typedef struct				s_save
{
	t_vec					o;
	t_vec					ray;
	t_vec					raytmp;
	t_tool					tool;
	t_obj					*objtmp;
	double					coefreflect;
	double					aliasreflect;
	double					n1;
	double					n2;
	double					gstate;
	int 					tab[NBOBJ];
}							t_save;
typedef struct s_var		t_var;
typedef void	(*t_tab)	(t_var *var);
typedef int 	(*t_tab2)	(t_var *var, double d);
typedef void	(*t_tab3)	(t_var *var, int i, t_vec *pt, t_obj *obj);
typedef void	(*t_tab4)	(t_var *var, t_obj *tobj, t_vec *pt);
typedef void	(*t_tab5)	(t_var *var, t_obj *obj);
struct						s_var
{
	t_mat					defaultmat;
	t_coef					coef;
	t_vec					raytmp;
	t_vec					pt;
	t_color					colorf;
	int						i;
	t_obj					obj[NBOBJ];
	t_obj					*curobj;
	t_light					light[NBLIGHT];
	t_light					ambiant;
	int						nblight;
	t_viewplane				viewplane;
	int						nbobj;
	t_cam					cam;
	t_vec					ray;
	t_obj					*objtmp;
	t_tab					tab[10];
	t_tab2					tab2[10];
	t_tab3					tab3[10];
	t_tab4					tab4[10];
	t_tab5					tab5[10];
	double					t;
	double					x_alias;
	double					y_alias;
	double					coefreflect;
	double					off_alias;
	double					aliasreflect;
	double					coefreflect_alias;
	double					coef_light;
	SDL_Texture				*sdl_tex;
	SDL_Window				*sdl_win;
	SDL_Renderer			*sdl_ren;
	SDL_Event				event;
	SDL_Surface				*surface;
	SDL_Surface				*surf;
	SDL_Surface				*text[NBTEXT];
	int						sizex;
	int						sizey;
	int						imgx;
	int						imgy;
	int						aliasing;
	int						endian;
	int						sizeline;
	int						bpp;
	int						depth;
	int						reflect;
	int						curdepth;
	int						curreflect;
	int						checkshad;
	int						gstate;
	int 					filter;
	t_inter					inter[2];
	t_inter					inter_light[2];
	double					koma[6];
	t_tool					tool;
	t_save					save;
	int 					nbi;
};
void						resetcolor(t_var *var);
int							ft_countc(char *s);
void						initvar(t_var *var);
void						initvar2(t_var *var);
void						init_koma(t_var *var);
void						initmat(t_var *var);
double						normvec(t_vec *vec);
void						ezvec(t_vec *a, t_vec *b, t_vec *vec);
t_vec						addvec(t_vec a, t_vec b);
t_vec						sousvec(t_vec a, t_vec b);
double						scal(t_vec *a, t_vec *b);
t_vec						prodvec(t_vec *u, t_vec *v);
void						initray(t_var *var);
t_vec						addvec3d(t_vec a, t_vec b);
t_vec						lenvec(t_vec vec, double len);
void						initvec(double x, double y, double z, t_vec *vec);
void						initviewplane(t_var *var);
void						ft_pixel_put(t_var *var, int color);
void						init_calc(t_var *var);
void						main_rt(t_var *var);
void						init_main_rt(t_var *var);
void						get_normal_cone(t_var *var, t_obj *tobj, t_vec *pt);
void						get_normal_test(t_var *var, t_obj *tobj, t_vec *pt);
void						get_normal_sphere(t_var *var, t_obj *tobj,
												t_vec *pt);
void						get_normal_paraboloid(t_var *var, t_obj *tobj,
												t_vec *pt);
void						get_normal_cylinder(t_var *var, t_obj *tobj,
												t_vec *pt);
void						get_normal_plan(t_var *var, t_obj *tobj, t_vec *pt);
void						makecolor(t_var *v, double c, t_obj *tobj, t_light *light);
void						makecolor2(t_var *v, double coef, t_light *light);
double						ft_dist(t_vec *a, t_vec *b);
void						ft_light(t_var *var, t_obj *cur);
int							ft_check(int ac, char **av);
int							ft_checks(char *s, t_var *var);
void						ft_parser(t_var *var, int ac, char **av);
void						ft_parsphere(char *s, t_var *var);
void						ft_parplan(char *s, t_var *var);
void						ft_parcone(char *s, t_var *var);
void						ft_parcylinder(char *s, t_var *var);
void						ft_parcam(char *s, t_var *var);
void						ft_parlight(char *s, t_var *var);
double						ft_sq(double a);
int							sort_inter(t_var *var, double x1, double x2);
void						sort_inter_light(t_var *var, double x1, double x2);
void						ft_checksphere3(t_var *var, t_obj *cur);
int							ft_checksphere2(t_var *var, double d);
void						ft_checksphere(t_var *var);
int							ft_checkparaboloid2(t_var *var, double d);
void						ft_checkparaboloid(t_var *var);
void						ft_checktest(t_var *var);
int							ft_checktest2(t_var *var, double d);
void						ft_checkplan(t_var *var);
int							ft_checkplan2(t_var *var, double d);
void						ft_checkplan3(t_var *var, t_obj *cur);
void						ft_checkcone(t_var *var);
int							ft_checkcone2(t_var *var, double d);
void						ft_checkcone3(t_var *var, t_obj *cur);
void						ft_checkcylinder(t_var *var);
int							ft_checkcylinder2(t_var *var, double d);
void						ft_checkcylinder3(t_var *var, t_obj *cur);
void						ft_checkdisk(t_var *var);
int							ft_checkdisk2(t_var *var, double d);
void						ft_printvec(t_vec *vec, char *s);
void						ft_1(t_equ *equ);
double						ft_2(t_equ *equ);
int							ft_22(t_equ *equ);
void						specular(t_var *var, t_light *light, t_obj *g);
void						coef_fresnel(t_var *var, t_obj *cur);
void						uprayreflect(t_var *var, t_vec *n);
void						upraytrans(t_var *var, t_vec *n, t_obj *cur);
double 						d_min(double x, double y);
double 						d_max(double x, double y);
double						minus(double x, double y);
double 						limit(t_var *var, t_equ *equ,
 										t_obj *cur, double t1);
double						limit_light(t_var *var, t_equ *equ,
	 									t_obj *cur, double t1);
double						cut(t_var *var, t_equ *equ, t_obj *cur, double t1);
double						cut_light(t_var *var, t_equ *equ,
										t_obj *cur, double t1);
void 						rev_vec(t_vec *t);
void 						make_text(t_var *var, double coef,
										t_obj* cur, t_light *light);
void 						new_texture(t_var *var, int fd);

int 						parser_xml(t_var *var, int ac, char **av);
int							get_c(char *s, char c);
double						get_cf(char *s, char c);
int							get_type(t_obj *cur, char *s);
void						get_vec(char *s, t_vec *vec);
void						get_radius(t_var *var, char *s);
t_color						get_color(char *s);
t_mat						new_mat( int fd);
void						preload(t_var *var);
void						new_config(t_var *var, int fd);
void						new_obj(t_var *var, int fd, t_obj *cur);
void						new_ambiant(t_var *var, int fd);
void						new_light(t_var *var, int fd, t_light *cur);
int 						ft_check_xml(int fd, char *line);
#endif
