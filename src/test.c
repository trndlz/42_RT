/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/11 17:33:29 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double          inter_sph(t_env *e, t_pt *tmp, t_pt *ve)
{
    double d;
    double t1;
    double t2;

    e->a = car(ve->x) + car(ve->y) + car(ve->z);
    e->b = 2 * (tmp->x * ve->x + tmp->y * ve->y + tmp->z * ve->z);
    e->c = car(tmp->x) + car(tmp->y) + car(tmp->z) - car(e->sp->r);
    d = car(e->b) - 4 * e->a * e->c;
    if (d < 0)
        return (0);
    t1 = (-e->b + sqrt(d)) / (2 * e->a);
    t2 = (-e->b - sqrt(d)) / (2 * e->a);
    if (d == 0)
        return (t1);
    else
        return (t1 < t2 ? t1 : t2);
}

double          inter_cyl(t_env *e, t_pt *tmp, t_pt *ve)
{
    double d;
    double t1;
    double t2;

    e->a = car(ve->x) + car(ve->y);
    e->b = 2 * (tmp->x * ve->x + tmp->y * ve->y);
    e->c = car(tmp->x) + car(tmp->y) - car(e->cy->r / 1.5);
    d = car(e->b) - 4 * e->a * e->c;
    if (d < 0)
        return (0);
    t1 = (-e->b + sqrt(d)) / (2 * e->a);
    t2 = (-e->b - sqrt(d)) / (2 * e->a);
    if (d == 0)
        return (t1);
    else
        return (t1 < t2 ? t1 : t2);
}

void            scene_plot(t_env *e)
{
    int         x;
    int         y;
    t_pt        *tmp;
    t_pt        *ve;
    double      t1;
    double      t2;

    y = 0;
    while (y < WINH)
    {
        x = 0;
        while (x < WINW)
        {
            tmp = init_pt(e->ey->x - e->sp->x0, e->ey->y - e->sp->y0, e->ey->z - e->sp->z0);
            ve = init_pt(WIND - e->ey->x, WINW / 2 - x - e->ey->y, WINH / 2 - y - e->ey->y);
            t1 = inter_sph(e, tmp, ve);
            free(tmp);
            tmp = init_pt(e->ey->x - e->cy->x0, e->ey->y - e->cy->y0, e->ey->z);
            t2 = inter_cyl(e, tmp, ve);
            if (!t1 && t2)
                draw_point(e, x, y, e->cy->color);
            if (t1 && !t2)
                draw_point(e, x, y, e->sp->color);
            if (t1 && t2 && t1 < t2)
                draw_point(e, x, y, e->sp->color);
            if (t1 && t2 && t1 >= t2)
                draw_point(e, x, y, e->cy->color);
            x++;
            free(tmp);
            free(ve);
        }
        y++;
    }
}

int main(void)
{

    t_env       *e;

    if (!(e = init_env()))
    {
        ft_putstr("Malloc error\n");
        return (0);
    }
    create_image(e);

    //mlx_hook(e->win, 2, 3, deal_key, e);
    //mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    //mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
