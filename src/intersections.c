/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/11 14:55:07 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
{
	t_vc abc;

	abc.x = vec_squ_sum(ray);
	abc.y = 2.0 * vec_x(offset, ray);
	abc.z = vec_squ_sum(offset) - car(obj->size);
	return (quadratic_solver(e, abc));
}

double			inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset)
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
	return (quadratic_solver(e, abc));
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
	t_vc abc;

	obj->rot = vec_norm(obj->rot);
	abc.x = vec_squ_sum(ray) - car(vec_x(ray, obj->rot));
	abc.y = 2 * (vec_x(ray, offset)
		- vec_x(ray, obj->rot) * vec_x(offset, obj->rot));
	abc.z = vec_squ_sum(offset)
		- car(vec_x(offset, obj->rot)) - car(obj->size);
	return (quadratic_solver(e, abc));
}

double			quadratic_solver(t_env *e, t_vc abc)
{
	double d;
	double t1;
	double t2;

	d = (double)car(abc.y) - (double)(4.0 * (abc.x * abc.z));
	// if (e->z == 541 && e->y == 609)
	// 	printf("noir d %f \n", d);
	// if (e->z == 348 && e->y == 157)
	// 	printf("pas noir d %f \n", d);
	if (d < 0)
		return (-1);
	t1 = (-abc.y + sqrt(d)) / (2.0 * abc.x);
	t2 = (-abc.y - sqrt(d)) / (2.0 * abc.x);
	// if (e->y == 541 && e->z == 609)
	// 	printf("t1 %f t2 %f \n", t1, t2);
	e->t1 = (t1 < t2 ? t1 : t2);
	e->t2 = (t1 < t2 ? t2 : t1);
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
