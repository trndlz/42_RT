/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 18:45:08 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	lighting_vectors(t_env *e, t_obj *obj, t_obj *llst)
{
	e->v = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
	e->lm = vec_sub(llst->pos, e->v);
	e->lm = rot_all_axis(e->lm, obj->rot);
	e->v = vec_sub(e->v, obj->pos);
	e->v = rot_all_axis(e->v, obj->rot);
	e->n = e->v;
	if (obj->type == 3)
		e->n.z = -e->t * e->ray.z / obj->size;
	if (obj->type == 2)
		e->n.z = obj->pos.z;
	if (obj->type == 4)
	{
		e->n = init_vc(0, 0, 100);
		e->n = rot_all_axis(e->n, obj->rot);
		e->n = (vec_x(e->n, vec_sub(obj->pos, e->eye_lookfrom)) < 0
		? e->n : vec_mult(e->n, -1));
	}
	if (obj->type != 4)
		e->n = rot_all_axis_inv(e->n, obj->rot);
	e->rm = vec_mult(e->n, 2 * vec_dot(e->lm, e->n));
	e->rm = vec_sub(e->rm, e->lm);
}

int		shadows(t_env *e, t_obj *tmp, t_obj *olst, t_obj *llst)
{
	double	s;
	int		nb_cross;
	t_vc	p;
	t_vc	light;
	t_vc	v2;

	nb_cross = 0;
	v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
	light = vec_mult(e->lm, -1.0);
	while (olst)
	{
		if (olst != tmp)
		{
			llst = e->light_link;
			while (llst)
			{
				light = rot_all_axis(vec_sub(v2, llst->pos), olst->rot);
				p = rot_all_axis(vec_sub(olst->pos, v2), olst->rot);
				s = distance_to_inter(e, olst, light, p);
				if (s > 0.0000001 && s < 0.999999)
					nb_cross++;
				llst = llst->next;
			}
		}
		olst = olst->next;
	}
	return (nb_cross);
}
