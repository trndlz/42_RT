/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_quadratic.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 18:10:41 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			inter_sph(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	t_vc abc;
	t_vc x;

	x = vec_sub(ray.origin, obj->pos);
	abc.x = vec_squ_sum(ray.direction);
	abc.y = 2.0 * vec_x(x, ray.direction);
	abc.z = vec_squ_sum(x) - car(obj->size);
	return (quadratic_solver(hit, abc));
}

double			inter_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	t_vc	v;
	t_vc	abc;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	k = obj->size;
	v = vec_norm(obj->rot);
	abc.x = vec_x(ray.direction, ray.direction) - car(vec_x(ray.direction, v));
	abc.y = 2 * (vec_x(ray.direction, x)
		- vec_x(ray.direction, v) * (vec_x(x, v) + 2 * k));
	abc.z = (vec_x(x, x) - vec_x(x, v) * (vec_x(x, v) + 4 * k));
	return (quadratic_solver(hit, abc));
}

double			inter_cone(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	t_vc	abc;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	k = 1 + car(tan(M_PI * obj->size / 180));
	obj->rot = vec_norm(obj->rot);
	abc.x = vec_x(ray.direction, ray.direction)
		- k * car(vec_x(ray.direction, obj->rot));
	abc.y = 2 * (vec_x(ray.direction, x)
		- k * vec_x(ray.direction, obj->rot)
		* vec_x(x, obj->rot));
	abc.z = vec_x(x, x)
		- k * car(vec_x(x, obj->rot));
	return (quadratic_solver(hit, abc));
}

double			inter_cyl(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	t_vc abc;
	t_vc x;

	x = vec_sub(ray.origin, obj->pos);
	obj->rot = vec_norm(obj->rot);
	abc.x = vec_squ_sum(ray.direction) - car(vec_x(ray.direction, obj->rot));
	abc.y = 2 * (vec_x(ray.direction, x)
		- vec_x(ray.direction, obj->rot) * vec_x(x, obj->rot));
	abc.z = vec_squ_sum(x)
		- car(vec_x(x, obj->rot)) - car(obj->size);
	return (quadratic_solver(hit, abc));
}
