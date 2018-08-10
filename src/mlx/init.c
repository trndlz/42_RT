/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/10 14:11:33 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->img_ori = (int *)malloc(sizeof(int) * WINY * WINZ)))
		return (NULL);
	e->eye_lookfrom = (t_vc){-1000, 0, 0};
	e->eye_rot = (t_vc){0, 0, 0};
	e->obj_link = NULL;
	e->light_link = NULL;
	e->cut_link = NULL;
	e->scene.filter = NO_FILTER;
	e->scene.antialias = 0;
	e->scene.blinding_lights = 0;
	e->scene.nr = 2;
	e->mlx.image = (void*)0;
	e->filter.img.pic = (void*)0;
	ft_memset(e->eq, '=', 51);
	return (e);
}

int			init_mlx(t_mlx *i_mlx)
{
	if (!(i_mlx->mlx = mlx_init()))
		return (0);
	if (!(i_mlx->win = mlx_new_window(i_mlx->mlx, WINY + LEG, WINZ, "RT")))
		return (0);
	return (1);
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
