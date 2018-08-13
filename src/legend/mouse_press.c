/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:18:34 by naminei           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:29 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		mouse_press_activated(t_env *e, t_vc rgb)
{
	e->filter.sld_r.pos_x = ((int)(rgb.x + 1) * (LEG / 2) / UCHAR_MAX)
		+ (LEG / 8) + WINY;
	e->filter.sld_g.pos_x = ((int)(rgb.y + 1) * (LEG / 2) / UCHAR_MAX)
		+ (LEG / 8) + WINY;
	e->filter.sld_b.pos_x = ((int)(rgb.z + 1) * (LEG / 2) / UCHAR_MAX)
		+ (LEG / 8) + WINY;
	e->filter.sld_s.pos_x = ((float)(e->click_obj->phong.x))
		* (LEG / 2) + (LEG / 8) + WINY;
	e->filter.sld_d.pos_x = ((float)(e->click_obj->phong.y))
		* (LEG / 2) + (LEG / 8) + WINY;
	e->filter.sld_a.pos_x = ((float)(e->click_obj->phong.z))
		* (LEG / 2) + (LEG / 8) + WINY;
}

static void		select_object(int x, int y, t_env *e)
{
	if (x >= 0 && y >= 0 && x <= WINY && y <= WINZ && e)
	{
		if ((e->click_obj = click_to_object(e, x, y)))
			e->filter.activate = 1;
		else
			e->filter.activate = 0;
	}
}

static void		click_for_filters(t_env *e, t_vc rgb)
{
	e->filter.activate = 0;
	e->click_obj = NULL;
	rgb = hextorgb(e->filter.tmp_col_f);
	e->filter.sld_r.pos_x = ((int)(rgb.x + 1) * (LEG / 2)
			/ UCHAR_MAX) + (LEG / 8) + WINY;
	e->filter.sld_g.pos_x = ((int)(rgb.y + 1) * (LEG / 2)
			/ UCHAR_MAX) + (LEG / 8) + WINY;
	e->filter.sld_b.pos_x = ((int)(rgb.z + 1) * (LEG / 2)
			/ UCHAR_MAX) + (LEG / 8) + WINY;
}

int				mouse_press(int button, int x, int y, t_env *e)
{
	t_vc	rgb;

	if (button == 1)
	{
		if (y <= 0)
			return (1);
		e->key[1] = 1;
		select_object(x, y, e);
		if (e->filter.activate == 1)
		{
			rgb = hextorgb(e->click_obj->col);
			mouse_press_activated(e, rgb);
		}
		if (x >= WINY && y >= 0 && x <= WINY + LEG && y <= 100 && e)
			click_for_filters(e, rgb);
		check_all_mouse(x, y, e);
		draw_all(e);
		mlx_put_image_to_window(e->mlx.mlx, e->mlx.win,
			e->filter.img.pic, WINY, 0);
		legend(e);
	}
	return (1);
}
