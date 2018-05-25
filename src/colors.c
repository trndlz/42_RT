/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/25 16:51:36 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				ratio_limits(double i)
{
	if (i < 0.00001)
		return (0);
	if (i > 1.0)
		return (1.0);
	else
		return (i);
}

int					color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

/*
** ka = ambient ratio
** kd = diffuse ratio
*/

unsigned long		rgb_to_hexa(t_obj *obj, t_env *e)
{
	int r;
	int g;
	int b;
	double dotdiffuse;
	double dotspecular;

	dotdiffuse = ratio_limits(e->cost);
	dotspecular = pow(vec_dot(&e->rm, &e->v), 50);
	dotspecular = ratio_limits(dotspecular);

	r = obj->color[0] * dotdiffuse + obj->ks * e->light->color[0] * dotspecular;
	g = obj->color[1] * dotdiffuse + obj->ks * e->light->color[1] * dotspecular;
	b = obj->color[2] * dotdiffuse + obj->ks * e->light->color[2] * dotspecular;

	r = color_limits(r);
	g = color_limits(g);
	b = color_limits(b);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
