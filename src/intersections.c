/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 18:34:25 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	e->a = (double)(vec_squ_sum(ray));
	e->b = (double)(2.0 * (double)vec_x(offset, ray));
	e->c = (double)vec_squ_sum(offset) - (double)car(obj->size);
	return (quadratic_solver(e));
}

double			inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	e->a = ray.x * ray.x + ray.y * ray.y - ray.z * ray.z / obj->size;
	e->b = 2.0 * ((offset.x * ray.x) + (offset.y * ray.y)
	- (offset.z * ray.z / obj->size));
	e->c = offset.x * offset.x + offset.y * offset.y - offset.z * offset.z
		/ obj->size;
	return (quadratic_solver(e));
}

double			inter_plane(t_vc ray, t_vc offset)
{
	double t;

	t = -offset.z / ray.z;
	if (t < 0)
		return (-1);
	return (t);
}

double			inter_cyl(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	e->a = car(ray.x) + car(ray.y);
	e->b = 2.0 * (vec_x(ray, offset) - ray.z * offset.z);
	e->c = car(offset.x) + car(offset.y) - car(obj->size);
	return (quadratic_solver(e));
}

double			quadratic_solver(t_env *e)
{
	double d;

	d = (double)car(e->b) - (double)(4.0 * (e->a * e->c));
	if (d < 0)
		return (-1);
	e->t1 = (-e->b + sqrt(d)) / (2.0 * e->a);
	e->t2 = (-e->b - sqrt(d)) / (2.0 * e->a);
	if (e->t1 < e->t2)
		return (e->t1);
	else
		return (e->t2);
}
