/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/25 18:49:36 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	e->a = vec_squ_sum(ray);
	e->b = 2.0 * vec_x(offset, ray);
	e->c = vec_squ_sum(offset) - car(obj->size);
	return (quadratic_solver(e));
}

double			inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	double k;
	double t;
	double m;

	if (obj->height == 0.0)
		k = 1 + car(tan(M_PI * obj->size / 180));
	else
		k = 1 + car(obj->size / obj->height);
	obj->rot = vec_norm(obj->rot);
	e->a = vec_x(ray, ray)
		- k * car(vec_x(ray, obj->rot));
	e->b = 2 * (vec_x(ray, offset)
		- k * vec_x(ray, obj->rot)
		* vec_x(offset, obj->rot));
	e->c = vec_x(offset, offset)
		- k * car(vec_x(offset, obj->rot));
	t = quadratic_solver(e);
	if (obj->height == 0.0)
		return (t);
	m = ((vec_x(e->ray, obj->rot) * t + vec_x(e->offset, obj->rot)));
	if (m >= 0 && m <= obj->height)
		return (t);
	return (-1.0);
}

double			inter_plane(t_vc ray, t_vc offset, t_obj *obj)
{
	double t;
	double den;

	den = vec_x(ray, obj->rot);
	if (den == 0)
		return (-1);
	t = -vec_x(offset, obj->rot) / den;
	if (t < 0)
		return (-1);
	return (t);
}

double			inter_disc(t_vc ray, t_vc offset, t_env *e, t_obj *obj)
{
	double	t;
	double	d;
	t_vc	p;

	t = inter_plane(ray, offset, obj);
	if (t > 0)
	{
		p = vec_sub(vec_add(vec_mult(ray, t), e->eye_lookfrom), obj->pos);
		d = sqrtf(vec_x(p, p));
		if (d <= obj->size)
			return (t);
	}
	return (-1.0);
}

double			inter_cyl(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	double t;
	double m;

	obj->rot = vec_norm(obj->rot);
	e->a = vec_squ_sum(ray) - car(vec_x(ray, obj->rot));
	e->b = 2 * (vec_x(ray, offset)
		- vec_x(ray, obj->rot) * vec_x(offset, obj->rot));
	e->c = vec_squ_sum(offset)
		- car(vec_x(offset, obj->rot)) - car(obj->size);
	t = quadratic_solver(e);
	if (!obj->height)
		return (t);
	m = vec_x(e->ray, obj->rot) * t + vec_x(e->offset, obj->rot);
	if (m >= 0 && m <= obj->height)
		return (t);
	return (-1.0);
}

double			quadratic_solver(t_env *e)
{
	double d;
	double t1;
	double t2;

	d = (double)car(e->b) - (double)(4.0 * (e->a * e->c));
	if (d < 0)
		return (-1);
	t1 = (-e->b + sqrt(d)) / (2.0 * e->a);
	t2 = (-e->b - sqrt(d)) / (2.0 * e->a);
	if (t2 > t1 && t1 < 0)
	{
		e->smax = t1;
		t1 = t2;
	}
	if (t2 < t1)
	{
		e->smax = t1;
		t1 = t2;
	}
	return (t1);
}
