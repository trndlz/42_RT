/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartooning.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:31:45 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/20 16:55:15 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

int		palette_compare(int *palette, int color)
{
		int	i;

		i = 0;
		while (palette[i] != -1 && i < PALETTE_SIZE)
		{
			if (clr_abs_dif(color, palette[i]) < CART_S)
				return (0);
			if (clr_abs_dif(color, palette[i]) >= CART_S)
				i++;
		}
		return (i);
}

int		palette_add(int *palette, int color)
{
	int i;

	i = -1;
	while (palette[++i] != -1 && i < PALETTE_SIZE)
	if (i <= PALETTE_SIZE)
		return (color);
	return (-1);
}

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

char	line_condition(int *imgstr, int y, int z)
{
	if (imgstr[z * WINY + y + WINY] != 0 && imgstr[z * WINY + y + 1] != 0 &&
	imgstr[z * WINY + y - WINY] != 0 && imgstr[z * WINY + y - 1] != 0 )
	if (major_color(imgstr[z * WINY + y]) !=
		major_color(imgstr[z * WINY + y + WINY])
	|| major_color(imgstr[z * WINY + y]) !=
		major_color(imgstr[z * WINY + y - WINY])
	|| major_color(imgstr[z * WINY + y]) !=
		major_color(imgstr[z * WINY + y + 1])
	|| major_color(imgstr[z * WINY + y]) !=
		major_color(imgstr[z * WINY + y - 1]))
		return (1);
	return (0);
}

void	cartooning(t_env *e)
{
	int *palette;
	palette = (int *)malloc(sizeof(int) * PALETTE_SIZE);
	int i;

	i = 0;
	printf("1 \n");
	while(i < PALETTE_SIZE)
	{
		palette[i] = -1;
		i++;
	}
	printf("2 \n");
	palette[0] = 0xffffff;
	i = 0;
	e->z = -1;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		if (palette_compare(palette, e->imgstr[e->z * WINY + e->y]) && i < PALETTE_SIZE)
			{
				palette[i] = palette_add(palette, e->imgstr[e->z * WINY + e->y]);
				i++;
			}
	}
	printf("3 \n");
	e->z = -1;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
			e->imgstr[e->z * WINY + e->y] = palette[closest_col(palette, e->imgstr[e->z * WINY + e->y])];
	}
	e->z = -1;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			if(line_condition(e->imgstr, e->y, e->z))
			{
				e->imgstr[e->z * WINY + e->y] = 0x000000;
				e->imgstr[e->z * WINY + e->y - WINY] = 0x000000;
				e->imgstr[e->z * WINY + e->y - 1] = 0x000000;
			}
		}
	}
	free(palette);
}
