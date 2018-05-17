/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:36 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 14:36:14 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	vec_squ_sum(t_vc *v1)
{
	if (!v1)
		return (0);
	return (car(v1->x) + car(v1->y) + car(v1->z));
}

t_vc	vec_sub(t_vc *v1, t_vc *v2)
{
	t_vc v;

	v.x = v1->x - v2->x;
	v.y = v1->y - v2->y;
	v.z = v1->z - v2->z;
	return (v);
}

double	vec_x(t_vc *v1, t_vc *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

double	vec_mod(t_vc *v)
{
	return (sqrt(vec_x(v, v)));
}

void	vec_norm(t_vc *v)
{
	double module;

	module = 1.0 / vec_mod(v);
	v->x *= module;
	v->y *= module;
	v->z *= module;
}

t_vc	vec_mult(t_vc *v, double a)
{
	t_vc ret;

	ret.x = v->x * a;
	ret.y = v->y * a;
	ret.z = v->z * a;
	return (ret);
}
