/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/23 14:46:19 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int             main(void)
{
    t_obj       *s1;
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
	e->light = new_light();
	e->link = NULL;
    s1 = new_sphere();
    obj_add(&e->link, s1);
    c1 = new_cylinder();
    //obj_add(&e->link, c1);
    c2 = new_cylinder();
    //obj_add(&e->link, c2);
    k1 = new_cone();
	//rot_x(&k1->rot, 0);
	//rot_y(&k1->rot, 0);
    obj_add(&e->link, k1);

    p1 = new_plane();
    //obj_add(&e->link, p1);
    create_image(e);
    mlx_hook(e->win, 2, 3, deal_key, e);
    //mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    //mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
