/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/16 11:46:33 by jostraye         ###   ########.fr       */
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
	e->v = init_vc(e->eye_lookfrom.x + e->t * e->ray.x, e->eye_lookfrom.y + e->t * e->ray.y, e->eye_lookfrom.z + e->t * e->ray.z);
	e->lm = init_vc(e->light->pos.x - e->v.x, e->light->pos.y - e->v.y, e->light->pos.z - e->v.z);
	e->lm = rot_all_axis(e->lm, obj->rot);
	e->v = vec_sub(e->v, obj->pos);
	e->v = rot_all_axis(e->v, obj->rot);
	// vec_norm(e->lm);
	e->n = e->v;
	if (obj->type == 3)
		e->n.z = - e->t * e->ray.z / obj->size;
	if(obj->type == 2)
		e->n.z = obj->pos.z;
	if (obj->type == 4)
	{
		e->n = init_vc(0, 0, 100);
		e->n = rot_all_axis(e->n, obj->rot);
		e->n = (vec_x(e->n, vec_sub(obj->pos, e->eye_lookfrom)) < 0 ? e->n : vec_mult(e->n, -1));
	}
	if (obj->type != 4)
		e->n = rot_all_axis_inv(e->n, obj->rot);
	// vec_norm(e->n);
	e->rm = vec_mult(e->n, 2 * vec_dot(e->lm, e->n));
	e->rm = vec_sub(e->rm, e->lm);
}
