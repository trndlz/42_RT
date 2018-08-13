/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartooning.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:54:45 by jostraye          #+#    #+#             */
/*   Updated: 2018/08/13 14:06:57 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	line_condition(int *imgstr, int y, int z)
{
	if (imgstr[z * WINY + y + WINY] != 0 && imgstr[z * WINY + y + 1] != 0
		&& imgstr[z * WINY + y - WINY] != 0 && imgstr[z * WINY + y - 1] != 0)
		if (major_color(imgstr[z * WINY + y])
			!= major_color(imgstr[z * WINY + y + WINY])
			|| major_color(imgstr[z * WINY + y])
			!= major_color(imgstr[z * WINY + y - WINY])
			|| major_color(imgstr[z * WINY + y])
			!= major_color(imgstr[z * WINY + y + 1])
			|| major_color(imgstr[z * WINY + y])
			!= major_color(imgstr[z * WINY + y - 1]))
			return (1);
	return (0);
}

void	flatten_colors(t_env *e, int *palette)
{
	int z;
	int y;

	z = -1;
	while (++z < WINZ)
	{
		y = -1;
		while (++y < WINY)
			e->imgstr[z * WINY + y] = palette[
					closest_col(palette, e->imgstr[z * WINY + y])];
		progression_bar(e, "Cartooning / Colors", (int)(100 * (z + 2) / WINZ));
	}
	ft_putchar('\n');
}

void	line(t_env *e)
{
	int y;
	int z;

	z = 0;
	while (++z < WINZ - 1)
	{
		y = 0;
		while (++y < WINY - 1)
		{
			if (line_condition(e->imgstr, y, z))
			{
				e->imgstr[z * WINY + y] = 0x000000;
				e->imgstr[z * WINY + y - WINY] = 0x000000;
				e->imgstr[z * WINY + y - 1] = 0x000000;
			}
		}
		progression_bar(e, "Cartooning / Process", (int)(100 * (z + 2) / WINZ));
	}
	ft_putchar('\n');
}

char	cartooning(t_env *e)
{
	int palette[PALETTE_SIZE];

	if (!(init_palette(palette)))
		return (0);
	if (!(create_palette(e, palette)))
		return (0);
	flatten_colors(e, palette);
	line(e);
	return (1);
}
