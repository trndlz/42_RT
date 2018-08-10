/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_legend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:17:54 by naminei           #+#    #+#             */
/*   Updated: 2018/08/10 08:18:09 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		check_mouse(int x, int y, t_slider *slider, t_cursor *cursor)
{
	if (x >= slider->pos_x_zero && x <= slider->pos_x_max \
		&& y <= cursor->end_pos.y && y >= cursor->start_pos.y)
	{
		if (x >= slider->pos_x_zero && x <= slider->pos_x_max)
			slider->pos_x = x;
	}
}

static void		check_all_mouse(int x, int y, t_env *e)
{
	check_mouse(x, y, &(e->filter.sld_r), &(e->filter.crs_r));
	check_mouse(x, y, &(e->filter.sld_g), &(e->filter.crs_g));
	check_mouse(x, y, &(e->filter.sld_b), &(e->filter.crs_b));
	if (e->filter.activate == 0)
	{
		check_mouse(x, y, &(e->filter.sld_i), &(e->filter.crs_i));
	}
	if (e->filter.activate == 1)
	{
		check_mouse(x, y, &(e->filter.sld_s), &(e->filter.crs_s));
		check_mouse(x, y, &(e->filter.sld_d), &(e->filter.crs_d));
		check_mouse(x, y, &(e->filter.sld_a), &(e->filter.crs_a));
	}
}

int				mouse(int x, int y, t_env *e)
{
	if (e->key[1] == 1)
	{
		check_all_mouse(x, y, e);
		draw_all(e);
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, \
			e->filter.img.pic, WINY, 0);
		legend(e);
	}
	return (1);
}

int				mykeyhook(int keycode, t_env *e)
{
	if (keycode)
		e->key[keycode] = 1;
	return (0);
}
