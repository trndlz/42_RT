/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/14 19:47:17 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double          inter_sph(t_env *e, t_vc tmp, t_vc ray, t_obj *obj)
{
    double d;
    double t1;
    double t2;

    e->a = vec_squ_sum(&ray);
    e->b = 2 * vec_cross_prod(&tmp, &ray);
    e->c = vec_squ_sum(&tmp) - car(obj->size);
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

double          inter_cyl(t_env *e, t_vc tmp, t_vc ray, t_obj *obj)
{
    double d;
    double t1;
    double t2;

    rot_all_axis(&ray, obj);
    e->a = car(ray.x) + car(ray.y);
    e->b = 2 * (tmp.x * ray.x + tmp.y * ray.y);
    e->c = car(tmp.x) + car(tmp.y) - car(obj->size);
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

t_obj          *nearest_node(t_env *e, t_obj *obj)
{
    double  t;
    t_obj   *tmp;
    t_obj   *ret;
    t_vc    offset;
    t_vc    ray;

    tmp = obj;
    t = 0;
    e->t = 800000;
    ret = NULL;
    while (tmp)
    {
        offset = vec_sub(&e->eye, &tmp->pos);
        e->init = init_vc(WIND, WINW / 2 - e->x, WINH / 2 - e->y);
        ray = vec_sub(&e->init, &e->eye);
        if (tmp->type == 1)
        {
            t = inter_sph(e, offset, ray, tmp);
        }
        if (tmp->type == 2)
        {
            t = inter_cyl(e, offset, ray, tmp);
        }
        if (t > 0.00001 && t < e->t)
        {
            e->t = t;
            ret = tmp;
        }
        tmp = tmp->next;
    }
    return (ret);
}

void            scene_plot(t_env *e)
{
    t_obj       *o;
    t_obj       *tmp;

    o = e->link;
    e->y = 0;
    while (e->y < WINH)
    {
        e->x = 0;
        while (e->x < WINW)
        {
            tmp = nearest_node(e, o);
            if (tmp)
                draw_point(e, e->x, e->y, tmp->color);
            e->x++;
        }
        e->y++;
    }
}

int main(void)
{

    t_obj       *s1;
    t_obj       *s2;
    t_obj       *c1;
    t_obj       *c2;
    t_env       *e;

    if (!(e = init_env()))
    {
        ft_putstr("Malloc error\n");
        return (0);
    }
    e->link = NULL;
    s1 = new_sphere(0);
    obj_add(&e->link, s1);
    s2 = new_sphere(1);
    obj_add(&e->link, s2);
    c1 = new_cylinder(0);
    obj_add(&e->link, c1);
    c2 = new_cylinder(10);
    obj_add(&e->link, c2);

    create_image(e);

    //mlx_hook(e->win, 2, 3, deal_key, e);
    //mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    //mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
