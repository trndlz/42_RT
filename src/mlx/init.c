/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 14:19:34 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

int			init_fct(t_env *e)
{
	int b;
	int s;
	int en;

	if (e->mlx.image)
		mlx_destroy_image(e->mlx.mlx, e->mlx.image);
	if (e->filter.img.pic)
		mlx_destroy_image(e->mlx.mlx, e->filter.img.pic);
	if (!(e->mlx.image = mlx_new_image(e->mlx.mlx, WINY, WINZ)))
		return (0);
	if (!(e->filter.img.pic = mlx_new_image(e->mlx.mlx, LEG, WINZ)))
		return (0);
	if (!(e->filter.img.info = mlx_get_data_addr(e->filter.img.pic,
					&e->filter.img.bpp, &e->filter.img.s_l,
					&e->filter.img.endian)))
		return (0);
	if (!(e->imgstr = (int *)mlx_get_data_addr(e->mlx.image, &b, &s, &en)))
		return (0);
	if (!multi_threading(e))
		return (0);
	return (0);
}
