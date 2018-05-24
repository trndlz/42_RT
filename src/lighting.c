/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/24 14:09:37 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** #### SYNTAX
** V * a = vec_mult(V, a) // a not a vector
** A | B = vec_cross_prod(A, B)
** A - B = vec_sub(A, B)
** A . B = vec_dot(A, B)
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

/*
** VECTORS
** v : direction pointing towards the viewer
** eye : eye/camera position
** lm : direction from surface point to (each) light source
** n : normal at this point of the surface
** rm : reflected ray of light from this point on the surface
*/

void	lighting_vectors(t_env *e, t_obj *obj)
{
	t_vc	tmp;
	double	k;

	e->v = init_vc(e->eye.x + e->t * e->ray.x, e->eye.y + e->t * e->ray.y, e->eye.y + e->t * e->ray.z);
	e->lm = init_vc(e->light->pos.x - e->v.x, e->light->pos.y - e->v.y, e->light->pos.z - e->v.z);
	vec_norm(&e->lm);
	if (obj->type == 1)
		e->n = e->v;
	if (obj->type == 2 || obj->type == 3)
	{
		k = e->t * vec_x(&e->ray, &obj->rot) + vec_x(&e->offset, &obj->rot);
		tmp = (obj->type == 2 ? vec_mult(&obj->rot, k) :
			vec_mult(&obj->rot, (k * (1 + car(tan(M_PI * obj->size / 180))))));
		e->n = vec_sub(&e->v, &tmp);
	}
	if (obj->type == 4)
		e->n = obj->rot;
	vec_norm(&e->n);
	//if (obj->type == 3)
	//{
	//	printf("x %f / y %f / z %f \n", e->n.x, e->n.y, e->n.z);
	//}
	e->rm = vec_mult(&e->n, 2 * vec_dot(&e->lm, &e->n));
	e->rm = vec_sub(&e->rm, &e->lm);
	vec_norm(&e->rm);
}
