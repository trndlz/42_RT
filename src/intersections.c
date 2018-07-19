/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/13 15:13:28 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_hit_rec *hit, t_obj *obj, t_vc ray, t_vc offset)
{
	t_vc abc;

	abc.x = vec_squ_sum(ray);
	abc.y = 2.0 * vec_x(offset, ray);
	abc.z = vec_squ_sum(offset) - car(obj->size);
	return (quadratic_solver(hit, abc));
}

double			inter_cone(t_hit_rec *hit, t_obj *obj, t_vc ray, t_vc offset)
{
	double	k;
	t_vc	abc;

	k = 1 + car(tan(M_PI * obj->size / 180));
	obj->rot = vec_norm(obj->rot);
	abc.x = vec_x(ray, ray)
		- k * car(vec_x(ray, obj->rot));
	abc.y = 2 * (vec_x(ray, offset)
		- k * vec_x(ray, obj->rot)
		* vec_x(offset, obj->rot));
	abc.z = vec_x(offset, offset)
		- k * car(vec_x(offset, obj->rot));
	return (quadratic_solver(hit, abc));
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

// double			inter_disc2(t_vc ray, t_vc offset, t_env *e, t_obj *obj)
// {
// 	double	t;
// 	double	d;
// 	t_vc	p;
//
// 	t = inter_plane(ray, offset, obj);
// 	if (t > 0)
// 	{
// 		p = vec_sub(vec_add(vec_mult(ray, t), e->eye_lookfrom), obj->pos);
// 		d = sqrtf(vec_x(p, p));
// 		if (d <= obj->size)
// 			return (t);
// 	}
// 	return (-1.0);
// }

double			inter_cyl(t_hit_rec *hit, t_obj *obj, t_vc ray, t_vc offset)
{
	t_vc abc;

	obj->rot = vec_norm(obj->rot);
	abc.x = vec_squ_sum(ray) - car(vec_x(ray, obj->rot));
	abc.y = 2 * (vec_x(ray, offset)
		- vec_x(ray, obj->rot) * vec_x(offset, obj->rot));
	abc.z = vec_squ_sum(offset)
		- car(vec_x(offset, obj->rot)) - car(obj->size);
	return (quadratic_solver(hit, abc));
}

double			t_calculator(double a, double b)
{
	if (a < 0.0000001)
	{
		if (b > 0.0000001)
			return (b);
		return (-1);
	}
	if (b < 0.0000001)
	{
		if (a > 0.0000001)
			return (a);
		return (-1);
	}
	if (a < b)
		return (a);
	return (b);
}

double			quadratic_solver(t_hit_rec *hit, t_vc abc)
{
	double d;
	double t1;
	double t2;

	d = (double)car(abc.y) - (double)(4.0 * (abc.x * abc.z));
	if (d < 0)
		return (-1);
	t1 = (-abc.y + sqrt(d)) / (2.0 * abc.x);
	t2 = (-abc.y - sqrt(d)) / (2.0 * abc.x);
	hit->t1 = t1;
	hit->t2 = t2;
	return (t_calculator(t1, t2));
}
