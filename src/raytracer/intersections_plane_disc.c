/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_plane_disc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 18:10:41 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_plane(t_ray ray, t_obj *obj)
{
	double	t;
	double	den;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	den = vec_x(ray.direction, obj->rot);
	if (den == 0)
		return (-1);
	t = -vec_x(x, obj->rot) / den;
	if (t < 0)
		return (-1);
	return (t);
}

double			inter_disc(t_obj *obj, t_ray ray)
{
	double	t;
	t_vc	p;

	t = inter_plane(ray, obj);
	if (t > 0)
	{
		p = vec_sub(inter_position(ray, t), obj->pos);
		if (obj->size > 0)
		{
			if (sqrtf(vec_x(p, p)) <= fabs(obj->size))
				return (t);
		}
		else
		{
			if (sqrtf(vec_x(p, p)) > fabs(obj->size))
				return (t);
		}
	}
	return (-1.0);
}
