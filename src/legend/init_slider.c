/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slider.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:17:04 by naminei           #+#    #+#             */
/*   Updated: 2018/08/11 18:12:53 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_each_slider(t_slider *slider, t_cursor *cursor)
{
	slider->pos_x_zero = WINY + (LEG / 8);
	slider->pos_x = slider->pos_x_zero;
	slider->pos_x_max = slider->pos_x_zero + (LEG / 2);
	cursor->height = 20;
	cursor->width = 10;
	cursor->cursor_vect.x = 0;
	cursor->cursor_vect.y = 0;
	slider->pos_x_length = (LEG / 2);
}

int				init_slider(t_env *e)
{
	e->click_obj = NULL;
	e->filter.sld_r.pos_y = 200;
	init_each_slider(&(e->filter.sld_r), &(e->filter.crs_r));
	e->filter.sld_g.pos_y = 250;
	init_each_slider(&(e->filter.sld_g), &(e->filter.crs_g));
	e->filter.sld_b.pos_y = 300;
	init_each_slider(&(e->filter.sld_b), &(e->filter.crs_b));
	e->filter.sld_i.pos_y = 350;
	init_each_slider(&(e->filter.sld_i), &(e->filter.crs_i));
	e->filter.sld_s.pos_y = 400;
	init_each_slider(&(e->filter.sld_s), &(e->filter.crs_s));
	e->filter.sld_d.pos_y = 450;
	init_each_slider(&(e->filter.sld_d), &(e->filter.crs_d));
	e->filter.sld_a.pos_y = 500;
	init_each_slider(&(e->filter.sld_a), &(e->filter.crs_a));
	e->filter.activate = 0;
	e->filter.intensity = .0;
	return (0);
}
