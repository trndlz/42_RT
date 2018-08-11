/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:26:45 by naminei           #+#    #+#             */
/*   Updated: 2018/08/11 17:59:35 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(t_env *e, int x, int y, int color)
{
	int		r;
	int		g;
	int		b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	if (y < WINZ && x < WINY + LEG)
	{
		e->filter.img.info[(y * e->filter.img.s_l) \
			+ ((e->filter.img.bpp / 8) * x) + 2] = r;
		e->filter.img.info[(y * e->filter.img.s_l) \
			+ ((e->filter.img.bpp / 8) * x) + 1] = g;
		e->filter.img.info[(y * e->filter.img.s_l) \
			+ ((e->filter.img.bpp / 8) * x)] = b;
	}
}

void	put_in_color(t_env *e)
{
	int x;
	int y;

	x = WINY;
	y = 0;
	while (y < WINZ)
	{
		while (x < WINY + LEG)
		{
			put_pixel(e, x, y, 0x17202A);
			x++;
		}
		x = WINY;
		y++;
	}
}
