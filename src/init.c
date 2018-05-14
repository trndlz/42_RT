/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/14 18:20:09 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->mlx = mlx_init()))
        return (NULL);
	if (!(e->win = mlx_new_window(e->mlx, WINW, WINH, "RTv1")))
        return (NULL);
    e->sp = init_sphere(0, 0, 0, 70);
    e->cy = init_cylinder(0, 0, 0, 35);
    e->eye = init_vc(-200, 0, 0);
	return (e);
}

t_vc        init_vc(double x, double y, double z)
{
    t_vc vc;

    vc.x = x;
    vc.y = y;
    vc.z = z;
    return (vc);
}

t_sphere    init_sphere(double x0, double y0, double z0, double r)
{
    t_sphere sp;

    sp.c = init_vc(x0, y0, z0);
    sp.r = r;
    sp.color = 0xE0115F;
    return (sp);
}

t_cylinder    init_cylinder(double x0, double y0, double z0, double r)
{
    t_cylinder cy;

    cy.c = init_vc(x0, y0, z0);
    cy.r = r;
    cy.color = 0x3EB489;
    return (cy);
}
