/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 18:16:47 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		closest_col(int *palette, int color)
{
	int min_diff;
	int	i;


	i = -1;
	min_diff = 3 * 256;
	while (palette[++i] != -1 && i < PALETTE_SIZE)
		if (clr_abs_dif(color, palette[i]) < min_diff)
			min_diff = clr_abs_dif(color, palette[i]);
	i = 0;
	while (palette[++i] != -1 && i < PALETTE_SIZE)
		if (clr_abs_dif(color, palette[i]) == min_diff)
			return (i);
	return (0);
}

int		major_color(int color)
{
		t_vc rgb;

		rgb = hextorgb(color);
		if (rgb.x > rgb.y && rgb.x > rgb.z)
			color = 0xFF0000;
		else if (rgb.y > rgb.x && rgb.y > rgb.z)
			color = 0x00FF00;
		else
			color = 0x0000FF;
		return (color);
}
