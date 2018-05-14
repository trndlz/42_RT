/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/14 19:39:05 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# define WINW 1000
# define WINH 500
# define WIND 20

typedef struct      s_vc
{
    double          x;
    double          y;
    double          z;
}                   t_vc;

typedef struct      s_sphere
{
    t_vc            c;
    double          r;
    unsigned long   color;
}                   t_sphere;

typedef struct      s_cylinder
{
    t_vc            c;
    double          z_min;
    double          r;
    unsigned long   color;
}                   t_cylinder;

typedef struct      s_screen
{
    int             winx;
    int             winy;
    int             d;
}                   t_screen;

typedef struct      s_obj
{
    int             type;
    t_vc            rot;
    t_vc            pos;
    double          size;
    unsigned long   color;
    struct s_obj    *next;
}                   t_obj;

typedef struct              s_env
{
    void            *mlx;
    void            *win;
    void            *image;
    int             *imgstr;
    int             bpp;
    int             s_l;
    int             endian;
    int             x;
    int             y;
    double          a;
    double          b;
    double          c;
    double          t;
    t_vc            tmp;
    t_vc            ve;
    t_vc            eye;
    t_vc            init;
    t_sphere        sp;
    t_cylinder      cy;
    t_obj           *link;
}                           t_env;


void                create_image(t_env *e);
void                draw_point(t_env *e, int x, int y, unsigned int color);
void                scene_plot(t_env *e);

/*
** MATHS
*/

double              car(double a);
void            rot_x(t_vc *vc, int t);
void            rot_y(t_vc *vc, int t);
void            rot_z(t_vc *vc, int t);
void            rot_all_axis(t_vc *vc, t_obj *obj);
double           vec_squ_sum(t_vc *v1);
t_vc            vec_sub(t_vc *v1, t_vc *v2);
double           vec_cross_prod(t_vc *v1, t_vc *v2);


/*
** STRUCTURES INITIALIZATION
*/

t_env               *init_env(void);
t_vc                init_vc(double x, double y, double z);
t_sphere            init_sphere(double x0, double y0, double z0, double r);
t_cylinder          init_cylinder(double x0, double y0, double z0, double r);

/*
** OBJECTS
*/

void                obj_add(t_obj **beg, t_obj *n);
t_obj		        *new_sphere(int x);
t_obj		        *new_sphere2(int x);
t_obj               *new_cylinder(int x);

#endif
