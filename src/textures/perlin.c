/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 12:20:15 by avinas            #+#    #+#             */
/*   Updated: 2018/08/13 13:54:45 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				*init_perm(void)
{
	int	*perm;
	int	i;

	if ((perm = (int *)malloc(sizeof(int) * 510)) == NULL)
		return (NULL);
	i = 0;
	srand(time(NULL));
	while (i < 510)
	{
		perm[i] = rand() % 255;
		i++;
	}
	return (perm);
}

t_file_texture	init_perlin(void)
{
	t_file_texture	tex;

	if (!(tex.size = (int *)malloc(sizeof(int) * 2)))
		exit_message("Error while creating Perlin malloc\n");
	tex.size[0] = PERL_S;
	tex.size[1] = PERL_S;
	if (!(tex.tab = (int **)malloc((sizeof(int *) * PERL_S) + 1)))
		exit_message("Error while creating Perlin malloc\n");
	return (tex);
}

int				calc_perlin_color(int color, t_obj *sphere)
{
	color = 65536 * color
		+ 256 * color + color;
	color = mix_colors(sphere->col, color, 0.5);
	return (color);
}

t_file_texture	create_perlin_tex(int res, t_obj *sphere)
{
	t_file_texture	tex;
	int				*perm;
	int				x;
	int				y;

	x = -1;
	tex = init_perlin();
	if (!(perm = init_perm()))
		exit_message("Error while creating Perlin malloc\n");
	while (++x < PERL_S)
	{
		if ((tex.tab[x] = (int *)malloc((sizeof(int) * PERL_S) + 1)) == NULL)
			exit_message("Error while creating Perlin malloc\n");
		y = -1;
		while (++y < PERL_S)
		{
			if ((tex.tab[x][y] = (perlin(x, y, res, perm) + 1)
				* 0.5 * 255) == -1)
				exit_message("Error while creating Perlin malloc\n");
			tex.tab[x][y] = calc_perlin_color(tex.tab[x][y], sphere);
		}
	}
	(perm) ? free(perm) : 0;
	return (tex);
}
