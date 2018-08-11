/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_perlin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:03:44 by avinas            #+#    #+#             */
/*   Updated: 2018/08/05 18:03:49 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			get_grad(int a, int b)
{
	float	unit;
	float	ret;

	unit = 1.0f / sqrt(2);
	((a == 0 && b == 0) || (a == 0 && b == 1) || (a == 1 && b == 1)
		|| (a == 2 && b == 0)) ? ret = unit : 0;
	((a == 1 && b == 0) || (a == 2 && b == 1)
		|| (a == 3 && b == 0) || (a == 3 && b == 1)) ? ret = -unit : 0;
	((a == 4 && b == 1) || (a == 5 && b == 1) || (a == 6 && b == 0)
		|| (a == 7 && b == 0)) ? ret = 0 : 0;
	((a == 4 && b == 0) || (a == 6 && b == 1)) ? ret = 1 : 0;
	((a == 5 && b == 0) || (a == 7 && b == 1)) ? ret = -1 : 0;
	return (ret);
}

float			*pondere(float x, float y, int *g_tab)
{
	float	t_x;
	float	t_y;
	float	*p_tab;
	float	*ret;

	if ((p_tab = (float *)malloc(sizeof(float) * 4)) == NULL)
		return (NULL);
	t_x = x - (int)(x);
	t_y = y - (int)(y);
	p_tab[0] = get_grad(g_tab[0], 0) * t_x + get_grad(g_tab[0], 1) * t_y;
	t_x = x - ((int)(x) + 1);
	t_y = y - (int)(y);
	p_tab[1] = get_grad(g_tab[1], 0) * t_x + get_grad(g_tab[1], 1) * t_y;
	t_x = x - (int)(x);
	t_y = y - ((int)(y) + 1);
	p_tab[2] = get_grad(g_tab[2], 0) * t_x + get_grad(g_tab[2], 1) * t_y;
	t_x = x - ((int)(x) + 1);
	t_y = y - ((int)(y) + 1);
	p_tab[3] = get_grad(g_tab[3], 0) * t_x + get_grad(g_tab[3], 1) * t_y;
	ret = p_tab;
	return (ret);
}

float			lissage(float x, float y, float *p_tab)
{
	float	calc_tab[5];
	float	x0;
	float	y0;

	x0 = (int)(x);
	y0 = (int)(y);
	calc_tab[0] = x - x0;
	calc_tab[1] = 3 * calc_tab[0] * calc_tab[0] - 2
		* calc_tab[0] * calc_tab[0] * calc_tab[0];
	calc_tab[3] = p_tab[0] + calc_tab[1] * (p_tab[1] - p_tab[0]);
	calc_tab[4] = p_tab[2] + calc_tab[1] * (p_tab[3] - p_tab[2]);
	calc_tab[0] = y - y0;
	calc_tab[2] = 3 * calc_tab[0] * calc_tab[0] - 2
		* calc_tab[0] * calc_tab[0] * calc_tab[0];
	(p_tab) ? free(p_tab) : 0;
	return (calc_tab[3] + calc_tab[2] * (calc_tab[4] - calc_tab[3]));
}

float			perlin(float x, float y, float res, unsigned int *perm)
{
	int		x0;
	int		y0;
	int		g_tab[4];
	float	*p_tab;

	x /= res;
	y /= res;
	x0 = (int)(x);
	y0 = (int)(y);
	g_tab[0] = perm[x0 % 255 + perm[y0 % 255]] % 8;
	g_tab[1] = perm[x0 % 255 + 1 + perm[y0 % 255]] % 8;
	g_tab[2] = perm[x0 % 255 + perm[y0 % 255 + 1]] % 8;
	g_tab[3] = perm[x0 % 255 + 1 + perm[y0 % 255 + 1]] % 8;
	if ((p_tab = pondere(x, y, g_tab)) == NULL)
		return (-1);
	return (lissage(x, y, p_tab));
}
