/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/23 14:50:50 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					ratio_limits(double i)
{
	if (i < 0.0)
		return (0.0);
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

	dotdiffuse = e->cost;
	//if (obj->type == 2)
		//printf("%f\n", e->cost);
	dotspecular = vec_dot(&e->rm, &e->v);
	r = obj->ka * dotdiffuse * obj->color[0];// + obj->kd * dotdiffuse * e->light->color[0] + obj->ks * pow(dotspecular, 20) * e->light->color[0];
	g = obj->ka * dotdiffuse * obj->color[1];// + obj->kd * dotdiffuse * e->light->color[1];// + obj->ks * pow(dotspecular, 20) * e->light->color[1];
	b = obj->ka * dotdiffuse * obj->color[2];// + obj->kd * dotdiffuse * e->light->color[2];// + obj->ks * pow(dotspecular, 20) * e->light->color[2];
	r = color_limits(r);
	g = color_limits(g);
	b = color_limits(b);

	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
