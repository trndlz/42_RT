/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/11 17:22:14 by tmervin          ###   ########.fr       */
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
    if (!(e->sp = init_sphere(0, 0, 0, 80)))
        return (NULL);
    if (!(e->cy = init_cylinder(-40, -10, 0, -100, 70)))
            return (NULL);
    if (!(e->ey = init_pt(-200, 10, 15)))
        return (NULL);
	return (e);
}

t_pt        *init_pt(double x, double y, double z)
{
    t_pt *pt;
    if (!(pt = (t_pt*)malloc(sizeof(t_pt))))
        return (NULL);
    pt->x = x;
    pt->y = y;
    pt->z = z;
    return (pt);
}

t_sphere    *init_sphere(double x0, double y0, double z0, double r)
{
    t_sphere *sp;
    if (!(sp = (t_sphere*)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->x0 = x0;
    sp->y0 = y0;
    sp->z0 = z0;
    sp->r = r;
    sp->color = 0xE0115F;
    return (sp);
}

t_cylinder    *init_cylinder(double x0, double y0, double z0, double z_min, double r)
{
    t_cylinder *cy;
    if (!(cy = (t_cylinder*)malloc(sizeof(t_cylinder))))
        return (NULL);
    cy->x0 = x0;
    cy->y0 = y0;
    cy->z0 = z0;
    cy->z_min = z_min;
    cy->r = r;
    cy->color = 0x3EB489;
    return (cy);
}
