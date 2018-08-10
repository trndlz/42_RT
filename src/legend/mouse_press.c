/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:18:34 by naminei           #+#    #+#             */
/*   Updated: 2018/08/10 08:18:46 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		mouse_press_activated(t_env *e, t_vc rgb)
{
	e->filter.sld_r.pos_x = ((int)(rgb.x + 1) * 200 / 255) \
		+ 50 + WINY;
	e->filter.sld_g.pos_x = ((int)(rgb.y + 1) * 200 / 255) \
		+ 50 + WINY;
	e->filter.sld_b.pos_x = ((int)(rgb.z + 1) * 200 / 255) \
		+ 50 + WINY;
	e->filter.sld_s.pos_x = ((float)(e->click_obj->phong.x)) \
		* 200 + 50 + WINY;
	e->filter.sld_d.pos_x = ((float)(e->click_obj->phong.y)) \
		* 200 + 50 + WINY;
	e->filter.sld_a.pos_x = ((float)(e->click_obj->phong.z)) \
		* 200 + 50 + WINY;
}

static void		select_object(int y, int z, t_env *e)
{
	if (y >= 0 && z >= 0 && y <= WINY && z <= WINZ && e)
	{
		if ((e->click_obj = click_to_object(e, y, z)))
			e->filter.activate = 1;
	}
}

int				mouse_press(int button, int y, int z, t_env *e)
{
	t_vc	rgb;

	if (button == 1)
	{
		e->key[button] = 1;
		select_object(y, z, e);
		if (e->filter.activate == 1)
		{
			rgb = hextorgb(e->click_obj->col);
			mouse_press_activated(e, rgb);
		}
		if (y >= WINY && z >= 0 && y <= WINY + LEG && z <= 100 && e)
		{
			e->filter.activate = 0;
			e->click_obj = NULL;
			rgb = hextorgb(e->filter.tmp_col_f);
			e->filter.sld_r.pos_x = ((int)(rgb.x + 1) \
					* 200 / 255) + 50 + WINY;
			e->filter.sld_g.pos_x = ((int)(rgb.y + 1) \
					* 200 / 255) + 50 + WINY;
			e->filter.sld_b.pos_x = ((int)(rgb.z + 1) \
					* 200 / 255) + 50 + WINY;
		}
	}
	return (1);
}
