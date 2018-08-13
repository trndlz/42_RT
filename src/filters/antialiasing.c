/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:26:30 by jostraye          #+#    #+#             */
/*   Updated: 2018/08/13 14:13:33 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		clr_abs_dif(int col1, int col2)
{
	t_vc	rgb1;
	t_vc	rgb2;
	int		ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb1 = vec_sub(rgb1, rgb2);
	ret = fabs(rgb1.x) + fabs(rgb1.y) + fabs(rgb1.z);
	return (ret);
}

int		av_col_four(int col1, int col2, int col3, int col4)
{
	t_vc	rgb[5];
	int		ret;

	rgb[1] = hextorgb(col1);
	rgb[2] = hextorgb(col2);
	rgb[3] = hextorgb(col3);
	rgb[4] = hextorgb(col4);
	rgb[0].x = color_limits((rgb[1].x + rgb[2].x + rgb[3].x + rgb[4].x) / 4);
	rgb[0].y = color_limits((rgb[1].y + rgb[2].y + rgb[3].y + rgb[4].y) / 4);
	rgb[0].z = color_limits((rgb[1].z + rgb[2].z + rgb[3].z + rgb[4].z) / 4);
	ret = rgb[0].x * 0x100 * 0x100 + rgb[0].y * 0x100 + rgb[0].z;
	return (ret);
}

char	aa_condition(int *imgstr, int y, int z, int sensib)
{
	if (clr_abs_dif(imgstr[z * WINY + y + 1],
			imgstr[z * WINY + y + WINY]) > sensib
			|| clr_abs_dif(imgstr[z * WINY + y + 1],
				imgstr[z * WINY + y - WINY]) > sensib
				|| clr_abs_dif(imgstr[z * WINY + y - 1],
					imgstr[z * WINY + y + WINY]) > sensib
					|| clr_abs_dif(imgstr[z * WINY + y - 1],
						imgstr[z * WINY + y - WINY]) > sensib)
		return (1);
	else
		return (0);
}

void	copy_img_array(int *imgstr, int *colorcopy)
{
	int z;
	int y;

	z = -1;
	while (++z < WINZ)
	{
		y = -1;
		while (++y < WINY)
		{
			if (colorcopy[z * WINY + y] != 0)
				imgstr[z * WINY + y] = colorcopy[z * WINY + y];
			else
				imgstr[z * WINY + y] = 0x000000;
		}
	}
}

void	antialias(int *img)
{
	int *colorcopy;
	int	z;
	int	y;
	int i;

	z = 0;
	if (!(colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ)))
		return ;
	copy_img_array(colorcopy, img);
	while (++z < WINZ - 1)
	{
		y = 0;
		while (++y < WINY - 1)
		{
			i = z * WINY + y;
			if (aa_condition(img, y, z, AA_S))
				colorcopy[i] = mix_colors(av_col_four(img[i + 1],
							img[i + WINY], img[i - WINY],
							img[i - 1]), img[i], 0.5);
		}
	}
	copy_img_array(img, colorcopy);
	free(colorcopy);
}
