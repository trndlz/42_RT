/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 15:02:44 by tmervin          ###   ########.fr       */
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
** #### NORMAL VECTORS
** P-C = eye + t * ray
** Sphere: nrm(P-C)
** Cylinder: nrm(P-C - V*m ) with m = D|V*t + X|V
** Cone: nrm(P-C - (1+k*k)*V*m )
** Plane: obj->rot if D|V > 0. Else : -V
*/

double		diffuse(t_env *e, t_obj *obj)
{
	t_vc	p;
	t_vc	light;
	t_vc	normal;
	t_vc	tmp;
	double	k;

	p = init_vc(e->eye.x + e->t * e->ray.x, e->eye.y + e->t * e->ray.y,
	e->eye.y + e->t * e->ray.z);
	light = init_vc(e->light.x - p.x, e->light.y - p.y, e->light.z - p.z);
	if (obj->type == 1)
		normal = p;
	if (obj->type == 2 || obj->type == 3)
	{
		k = e->t * vec_x(&e->ray, &obj->rot) + vec_x(&e->offset, &obj->rot);
		tmp = (obj->type == 2 ? vec_mult(&obj->rot, k) :
			vec_mult(&obj->rot, (k * (1 + car(tan(obj->size))))));
		normal = vec_sub(&p, &tmp);
	}
	if (obj->type == 4)
		normal = (vec_x(&e->ray, &obj->rot) > 0 ? obj->rot :
			vec_mult(&obj->rot, -1));
	vec_norm(&normal);
	return (vec_x(&normal, &light) / (vec_mod(&normal) * vec_mod(&light)));
}
