/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/21 10:48:56 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_vectors(t_env *e, t_obj *obj)
{
	double m;

	e->v = vec_add(vec_mult(e->ray, e->t), e->offset);
	e->n = e->v;
	m = vec_x(e->ray, obj->rot) * e->t + vec_x(e->offset, obj->rot);
	if (obj->type == 3 || obj->type == 2)
	{
		if (obj->type == 3)
			m *= (1 + car(tan(M_PI * obj->size / 180)));
		e->n = vec_sub(vec_add(vec_mult(e->ray, e->t), e->offset),
		vec_mult(obj->rot, m));
	}
	if (obj->type == 4)
		e->n = obj->rot;
	e->n = vec_norm(e->n);
}

int		shadows(t_env *e, t_obj *tmp, t_obj *olst, t_obj *light_obj)
{
	double	s;
	t_vc	p;
	t_vc	light;
	t_vc	v2;

	v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
	light = vec_mult(e->lm, -1.0);
	while (olst)
	{
		// tmp += 0;
		light = vec_sub(v2, light_obj->pos);
		p = vec_sub(olst->pos, v2);
		s = distance_to_inter(e, olst, light, p);
		if (olst == tmp && olst->type != 4)
			s = e->smax;
		if (e->y == 533 && e->z == 490 && olst->type == 1)
		{
			printf("s %f\n", s);
		}
		if (s > 0.000001 && s < 0.99999)
			return (0);
		olst = olst->next;
	}
	return (1);
}
