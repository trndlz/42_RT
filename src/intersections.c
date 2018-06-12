/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/12 18:41:32 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** #### SYNTAX
** V * a = vec_mult(V, a)
** A | B = vec_cross_prod(A, B)
** A - B = vec_sub(A, B)
** nrm(A) = vec_cross_prod(A, B) / (vec_module(A) * vec_module(B))
*/

/*
** #### QUADRATIC COEF CALCULATION
** P-C = eye + t * ray
** Sphere: a = D|D ; b = D|X ; c = X|X - r*r
** Cylinder: a = D|D-(D|V)^2; b/2= D|X-(D|V)*(X|V); c = X|X- X|V)^2-r*r
** Cone:
** Plane:
*/

double			inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	e->a = vec_squ_sum(&ray);
	e->b = 2 * vec_x(&offset, &ray);
	e->c = vec_squ_sum(&offset) - car(obj->size);
	return (quadratic_solver(e));
}

double			inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	double k;

	vec_norm(&obj->rot);
	k = 1 + car(tan(M_PI * obj->size / 180));
	e->a = vec_squ_sum(&ray)
		- k * car(vec_x(&ray, &obj->rot));
	e->b = 2 * (vec_x(&ray, &offset)
		- k * vec_x(&ray, &obj->rot)
		* vec_x(&offset, &obj->rot));
	e->c = vec_squ_sum(&offset)
		- k * car(vec_x(&offset, &obj->rot));
	return (quadratic_solver(e));
}

double			inter_plane(t_obj *obj, t_vc ray, t_vc offset)
{
	double t;

	vec_norm(&obj->rot);
	t = ((vec_x(&obj->rot, &obj->pos) - vec_x(&obj->rot, &offset)) / vec_x(&obj->rot, &ray));
	if (t < 0)
		return (-1);
	return (t);
}

double			inter_cyl(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	vec_norm(&obj->rot);
	e->a = vec_squ_sum(&ray) - car(vec_x(&ray, &obj->rot));
	e->b = 2 * (vec_x(&ray, &offset)
		- vec_x(&ray, &obj->rot) * vec_x(&offset, &obj->rot));
	e->c = vec_squ_sum(&offset)
		- car(vec_x(&offset, &obj->rot)) - car(obj->size);
	return (quadratic_solver(e));
}

double			quadratic_solver(t_env *e)
{
	double d;

	d = car(e->b) - 4 * (e->a * e->c);
	if (d < 0)
		return (-1);
	e->t1 = (-e->b + sqrt(d)) / (2 * e->a);
	e->t2 = (-e->b - sqrt(d)) / (2 * e->a);
	if (e->t2 > e->t1 && e->t1 < 0)
		e->t1 = e->t2;
	if (e->t2 < e->t1)
		e->t1 = e->t2;
	return (e->t1);
}
