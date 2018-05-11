/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/11 16:44:07 by tmervin          ###   ########.fr       */
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

typedef struct      s_pt
{
    double          x;
    double          y;
    double          z;
}                   t_pt;

typedef struct      s_sphere
{
    double          x0;
    double          y0;
    double          z0;
    double          r;
    unsigned long   color;
}                   t_sphere;

typedef struct      s_cylinder
{
    double          x0;
    double          y0;
    double          z0;
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

typedef struct              s_env
{
    void            *mlx;
    void            *win;
    void            *image;
    int             *imgstr;
    int             bpp;
    int             s_l;
    int             endian;
    double          a;
    double          b;
    double          c;
    t_pt            *tmp;
    t_pt            *ve;
    t_pt            *ey;
    t_sphere        *sp;
    t_cylinder      *cy;
}                           t_env;


void                create_image(t_env *e);
void                draw_point(t_env *e, int x, int y, unsigned int color);
void                scene_plot(t_env *e);

/*
** MATHS
*/

double              car(double a);

/*
** STRUCTURES INITIALIZATION
*/

t_env               *init_env(void);
t_pt                *init_pt(double x, double y, double z);
t_sphere            *init_sphere(double x0, double y0, double z0, double r);
t_cylinder          *init_cylinder(double x0, double y0, double z0, double z_min, double r);

#endif
