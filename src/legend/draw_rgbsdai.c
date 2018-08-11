/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rgbsdai.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:15:34 by naminei           #+#    #+#             */
/*   Updated: 2018/08/10 15:49:03 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		draw_sliders(t_env *e, t_slider *slider)
{
	slider->pos_tmp = slider->pos_x_zero;
	while (slider->pos_tmp < slider->pos_x_max && slider->pos_tmp > 0)
	{
		put_pixel(e, slider->pos_tmp - (LEG / 2), slider->pos_y, 0x0000ff);
		slider->pos_tmp++;
	}
	return (slider->pos_x_max - slider->pos_x_zero);
}

int		draw_cursors(t_env *e, t_slider *slider, t_cursor *cursor)
{
	cursor->start_pos.x = slider->pos_x - cursor->width / 2 - (LEG / 2);
	cursor->end_pos.x = slider->pos_x + cursor->width / 2;
	cursor->start_pos.y = slider->pos_y - cursor->height / 2;
	cursor->end_pos.y = slider->pos_y + cursor->height / 2;
	while (cursor->start_pos.y < cursor->end_pos.y \
		&& cursor->end_pos.y < WINY + LEG)
	{
		while (cursor->start_pos.x < cursor->end_pos.x - (LEG / 2))
		{
			put_pixel(e, cursor->start_pos.x, cursor->start_pos.y, 0x00ffff);
			cursor->start_pos.x++;
		}
		cursor->start_pos.y++;
		cursor->start_pos.x = slider->pos_x - cursor->width / 2 - (LEG / 2);
	}
	cursor->start_pos.y -= cursor->height;
	return (1);
}

void	draw_all(t_env *e)
{
	put_in_color(e);
	draw_sliders(e, &(e->filter.sld_r));
	draw_cursors(e, &(e->filter.sld_r), &(e->filter.crs_r));
	draw_sliders(e, &(e->filter.sld_g));
	draw_cursors(e, &(e->filter.sld_g), &(e->filter.crs_g));
	draw_sliders(e, &(e->filter.sld_b));
	draw_cursors(e, &(e->filter.sld_b), &(e->filter.crs_b));
	if (e->filter.activate == 0)
	{
		draw_sliders(e, &(e->filter.sld_i));
		draw_cursors(e, &(e->filter.sld_i), &(e->filter.crs_i));
	}
	if (e->filter.activate == 1)
	{
		draw_sliders(e, &(e->filter.sld_s));
		draw_cursors(e, &(e->filter.sld_s), &(e->filter.crs_s));
		draw_sliders(e, &(e->filter.sld_d));
		draw_cursors(e, &(e->filter.sld_d), &(e->filter.crs_d));
		draw_sliders(e, &(e->filter.sld_a));
		draw_cursors(e, &(e->filter.sld_a), &(e->filter.crs_a));
	}
}

char	*write_obj(t_obj *click_obj)
{
	if (click_obj == NULL)
		return ("FILTERS");
	if (click_obj->o_type)
	{
		if (click_obj->o_type == SPHERE)
			return ("SPHERE");
		if (click_obj->o_type == CYLINDER)
			return ("CYLINDER");
		if (click_obj->o_type == CONE)
			return ("CONE");
		if (click_obj->o_type == PLANE)
			return ("PLANE");
		if (click_obj->o_type == DISC)
			return ("DISK");
		if (click_obj->o_type == PARABOLOID)
			return ("PARABOLOID");
	}
	return (NULL);
}
