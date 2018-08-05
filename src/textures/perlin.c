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

unsigned int	*init_perm(void)
{
	unsigned int	*perm;
	int				i;

	if ((perm = (unsigned int *)malloc(sizeof(unsigned int) * 500)) == NULL)
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
	if ((tex.tab = (int **)malloc((sizeof(int *) * PERL_S) + 1)) == NULL)
		ft_malloc_error(e);
	return (tex);
}

t_file_texture	create_perlin_tex(int res, t_env *e)
{
	t_file_texture	tex;
	unsigned int	*perm;
	int				x;
	int				y;

	x = 0;
	tex = init_perlin(e);
	perm = init_perm();
	while (x < PERL_S)
	{
		if ((tex.tab[x] = (int *)malloc((sizeof(int) * PERL_S) + 1)) == NULL)
			ft_malloc_error(e);
		y = 0;
		while (y < PERL_S)
		{
			if ((tex.tab[x][y] = (perlin(x, y, res, perm) + 1)
				* 0.5 * 255) == -1)
				ft_malloc_error(e);
			y++;
		}
		x++;
	}
	(perm) ? free(perm) : 0;
	return (tex);
}
