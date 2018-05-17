/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 14:35:12 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_env *e, t_obj *obj)
{
	e->a = vec_squ_sum(&e->ray);
	e->b = 2 * vec_x(&e->offset, &e->ray);
	e->c = vec_squ_sum(&e->offset) - car(obj->size);
	return (quadratic_solver(e));
}

double			inter_cone(t_env *e, t_obj *obj)
{
	double k;

	vec_norm(&obj->rot);
	k = 1 + car(tan(obj->size));
	e->a = vec_x(&e->ray, &e->ray)
		- k * car(vec_x(&e->ray, &obj->rot));
	e->b = 2 * (vec_x(&e->ray, &e->offset)
		- k * vec_x(&e->ray, &obj->rot)
		* vec_x(&e->offset, &obj->rot));
	e->c = vec_x(&e->offset, &e->offset)
		- k * car(vec_x(&e->offset, &obj->rot));
	return (quadratic_solver(e));
}

double			inter_plane(t_env *e, t_obj *obj)
{
	double t;

	vec_norm(&obj->rot);
	t = -vec_x(&e->offset, &obj->rot) / vec_x(&e->ray, &obj->rot);
	if (t < 0.00001)
		return (-1);
	return (t);
}

double			inter_cyl(t_env *e, t_obj *obj)
{
	vec_norm(&obj->rot);
	e->a = vec_x(&e->ray, &e->ray) - car(vec_x(&e->ray, &obj->rot));
	e->b = 2 * (vec_x(&e->ray, &e->offset)
		- vec_x(&e->ray, &obj->rot) * vec_x(&e->offset, &obj->rot));
	e->c = vec_x(&e->offset, &e->offset)
		- car(vec_x(&e->offset, &obj->rot)) - car(obj->size);
	return (quadratic_solver(e));
}

double			quadratic_solver(t_env *e)
{
	double d;
	double t1;
	double t2;

	d = car(e->b) - 4 * e->a * e->c;
	if (d < 0.00001)
		return (-1);
	t1 = (-e->b + sqrt(d)) / (2 * e->a);
	t2 = (-e->b - sqrt(d)) / (2 * e->a);
	if (d == 0)
		return (t1);
	else
		return (t1 < t2 ? t1 : t2);
}
