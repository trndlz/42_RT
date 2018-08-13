/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:16:36 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:32 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_vc	vec_norm(t_vc v)
{
	t_vc	ret;
	double	module;

	module = vec_mod(v);
	ret.x = v.x / module;
	ret.y = v.y / module;
	ret.z = v.z / module;
	return (ret);
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
