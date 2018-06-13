/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/13 17:04:02 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int             main(void)
{
    t_obj       *s1;
	t_obj       *s2;
	t_obj       *s3;
	t_obj       *s4;
    t_obj       *c1;
    t_obj       *c2;
    t_obj       *k1;
    t_obj       *p1;
	t_obj       *p2;
	t_obj       *p3;
    t_env       *e;

    if (!(e = init_env()))
    {
        ft_putstr("Malloc error\n");
        return (0);
    }
	e->light = new_light();
	e->link = NULL;
    s1 = new_sphere(0);
    obj_add(&e->link, s1);
	s2 = new_sphere(2);
    //obj_add(&e->link, s2);
	s3 = new_sphere(4);
    //obj_add(&e->link, s3);
	s4 = new_sphere(6);
    //obj_add(&e->link, s4);
    c1 = new_cylinder(2);
    obj_add(&e->link, c1);
    c2 = new_cylinder(5);
    obj_add(&e->link, c2);
    k1 = new_cone();
	//rot_x(&k1->rot, 0);
	//rot_y(&k1->rot, 0);
    obj_add(&e->link, k1);
    p1 = new_plane(1550, 0, 0);
    obj_add(&e->link, p1);
	p2 = new_plane(0, 50, 0);
    // obj_add(&e->link, p2);
	p3 = new_plane(0, 0, 50);
    //obj_add(&e->link, p3);
    create_image(e);
    mlx_hook(e->win, 2, 3, deal_key, e);
    //mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
