/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 14:35:54 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	lighting_vectors(t_env *e, t_obj *obj, t_obj *light_list)
{
	t_vc n_n;
	t_vc n_lm;

	e->v = init_vc(e->eye_lookfrom.x + e->t * e->ray.x, e->eye_lookfrom.y + e->t * e->ray.y, e->eye_lookfrom.z + e->t * e->ray.z);
	e->lm = init_vc(light_list->pos.x - e->v.x, light_list->pos.y - e->v.y, light_list->pos.z - e->v.z);
	e->lm = rot_all_axis(e->lm, obj->rot);
	e->v = vec_sub(e->v, obj->pos);
	e->v = rot_all_axis(e->v, obj->rot);
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
	n_n = e->n;
	vec_norm(n_n);
	n_lm = e->lm;
	vec_norm(n_lm);
	e->rm = vec_mult(n_n, 2 * vec_dot(n_lm, n_n));
	e->rm = vec_sub(e->rm, n_lm);
}
