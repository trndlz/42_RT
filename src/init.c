/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/14 13:53:34 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->vport = (t_vport*)malloc(sizeof(t_vport))))
		return (NULL);
	if (!(e->mlx = mlx_init()))
		return (NULL);
	if (!(e->win = mlx_new_window(e->mlx, WINY, WINZ, "RTv1")))
		return (NULL);
	e->eye_lookfrom = init_vc(-1000, 200, 0);
	e->eye_rot = init_vc(0, 0, 0);
	return (e);
}

t_vc		init_vc(double x, double y, double z)
{
	t_vc vc;

	vc.x = (double)x;
	vc.y = (double)y;
	vc.z = (double)z;
	return (vc);
}

void		obj_add(t_obj **beg, t_obj *n)
{
	if (!beg || !n)
		return ;
	else
	{
		n->next = *beg;
		*beg = n;
	}
}
