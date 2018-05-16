/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/16 16:11:44 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
            t = inter_sph(e, offset, ray, tmp);
        if (tmp->type == 2)
            t = inter_cyl(e, offset, ray, tmp);
        if (tmp->type == 3)
            t = inter_cone(e, offset, ray, tmp);
        if (tmp->type == 4)
            t = inter_plane(offset, ray, tmp);
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

int             main(void)
{
    t_obj       *s1;
    t_obj       *s2;
    t_obj       *c1;
    t_obj       *c2;
    t_obj       *k1;
    t_obj       *p1;
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
    k1 = new_cone(10);
    obj_add(&e->link, k1);
    p1 = new_plane();
    obj_add(&e->link, p1);
    create_image(e);
    //mlx_hook(e->win, 2, 3, deal_key, e);
    //mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    //mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
