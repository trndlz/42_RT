/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 12:20:15 by avinas            #+#    #+#             */
/*   Updated: 2018/08/05 17:40:06 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				*init_perm(void)
{
	int	*perm;
	int	i;

	if ((perm = (int *)malloc(sizeof(int) * 510)) == NULL)
		return (NULL);
	i = 0;
	srand(time(NULL));
	while (i < 500)
	{
		perm[i] = rand() % 255;
		i++;
	}
	return (perm);
}

t_file_texture	init_perlin(t_env *e)
{
	t_file_texture	tex;

	if (!(tex.size = (int *)malloc(sizeof(int) * 2)))
		ft_malloc_error(e);
	tex.size[0] = PERL_S;
	tex.size[1] = PERL_S;
	if (!(tex.tab = (int **)malloc((sizeof(int *) * PERL_S) + 1)))
		ft_malloc_error(e);
	return (tex);
}

int				calc_perlin_color(int color, t_obj *sphere)
{
	color = 65536 * color
		+ 256 * color + color;
	color = mix_colors(sphere->col, color, 0.5);
	return (color);
}

t_file_texture	create_perlin_tex(int res, t_env *e, t_obj *sphere)
{
	t_file_texture	tex;
	int				*perm;
	int				x;
	int				y;

	x = -1;
	tex = init_perlin(e);
	if (!(perm = init_perm()))
		ft_malloc_error(e);
	while (++x < PERL_S)
	{
		if ((tex.tab[x] = (int *)malloc((sizeof(int) * PERL_S) + 1)) == NULL)
			ft_malloc_error(e);
		y = -1;
		while (++y < PERL_S)
		{
			if ((tex.tab[x][y] = (perlin(x, y, res, perm) + 1)
				* 0.5 * 255) == -1)
				ft_malloc_error(e);
			tex.tab[x][y] = calc_perlin_color(tex.tab[x][y], sphere);
		}
	}
	(perm) ? free(perm) : 0;
	return (tex);
}
