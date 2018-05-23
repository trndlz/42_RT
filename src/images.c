/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:37:05 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/23 11:05:33 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			create_image(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	e->image = mlx_new_image(e->mlx, WINW, WINH);
	e->imgstr = (int *)mlx_get_data_addr(e->image, &e->bpp, &e->s_l,
			&e->endian);
	scene_plot(e);
	mlx_put_image_to_window(e->mlx, e->win, e->image, 0, 0);
	mlx_destroy_image(e->mlx, e->image);
}

void			draw_point(t_env *e, int x, int y, unsigned int color)
{
	int i;

	i = (x + ((y * e->s_l) / 4));
	if (i >= 0 && i < (WINW * WINH))
		e->imgstr[i] = color;
}
