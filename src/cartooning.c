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


void	flatten_colors(t_env *e, int *palette)
{
	e->z = -1;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
			e->imgstr[e->z * WINY + e->y] = palette[closest_col(palette, e->imgstr[e->z * WINY + e->y])];
	}
}

void	line(t_env *e)
{
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
}

char	cartooning(t_env *e)
{
	int *colorcopy;
	int *palette;

	palette = (int *)malloc(sizeof(int) * PALETTE_SIZE);
	colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ);
	if (!(init_palette(palette)))
		return (0);
	if(!(create_palette(e, palette)))
		return (0);
	flatten_colors(e, palette);
	line(e);
	free(palette);
	return (1);
}

double		blinding_condition(t_env *e, t_vc light)
{
	double coef;
	if (light.x == 0 || e->y - light.y == 0)
		return (1);
	else
		coef = 1 / (fabs(e->y - light.y) * sqrt(fabs(e->z - light.z))) * WINY * 100 / light.x +
		1 / (fabs(e->z - light.z) * sqrt(fabs(e->y - light.y))) * WINZ * 100 / light.x;
	if (coef > 1)
		coef = 1;
	return (coef);
}

void	blinding_lights(t_env *e)
{
	t_vc	light;
	light.x = 150;
	light.y = 500;
	light.z = 500;
	double		bld_coef;
	e->z = -1;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			if((bld_coef = blinding_condition(e, light)))
			{
				e->imgstr[e->z * WINY + e->y] = mix_colors(0xFFFFFF, e->imgstr[e->z * WINY + e->y], bld_coef);
			}
		}
	}
}
