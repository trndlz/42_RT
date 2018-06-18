/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:36 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 18:43:50 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	vec_squ_sum(t_vc v1)
{
	return (car(v1.x) + car(v1.y) + car(v1.z));
}

t_vc	vec_sub(t_vc v1, t_vc v2)
{
	t_vc v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vc	vec_add(t_vc v1, t_vc v2)
{
	t_vc v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

double	vec_dot(t_vc v1, t_vc v2)
{
	return (vec_x(v1, v2) / (vec_mod(v1) * vec_mod(v2)));
}

t_vc	vec_mult(t_vc v, double a)
{
	t_vc ret;

	ret.x = v.x * a;
	ret.y = v.y * a;
	ret.z = v.z * a;
	return (ret);
}
