/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/28 10:30:20 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_vectors(t_env *e, t_obj *obj)
{
	double m;

	e->v = vec_add(vec_mult(e->ray, e->t), e->offset);
	e->n = e->v;
	if (obj->type == 4 || obj->type == 5)
	{
		m = vec_x(e->ray, obj->rot) * e->t + vec_x(e->offset, obj->rot);
		if (obj->type == 5)
				m *= 1 + car(tan(M_PI * obj->size / 180));
		e->n = vec_sub(vec_add(vec_mult(e->ray, e->t), e->offset), vec_mult(obj->rot, m));
	}
	if (obj->type == 6)
		e->n = obj->rot;
	if (obj->type == 7)
		e->n = vec_mult(obj->rot, 1);
	e->n = vec_norm(e->n);
}

int	shadow_no_cutter(t_env *e, t_obj *obj, t_obj *tmp, t_obj *light_obj)
{
		double	s;
		t_vc	p;

	t_vc	light;
	t_vc	v2;
	t_vc	inter;

	v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
	if (tmp != obj)
	{
		light = vec_sub(v2, light_obj->pos);
		p = vec_sub(obj->pos, v2);
		s = distance_to_inter(e, obj, light, p);
		inter = vec_add(vec_mult(light, s), light_obj->pos);
		if (e->y == 501 && e->z == 417)
			printf("p %f %f %f s %f\n", p.x, p.y, p.z, s);

		if (obj == tmp && obj->type != 6 && obj->type != 7)
			s = e->smax;
		if (s > 0.000001 && s < 0.99999)
			return (0);
	}
	return (1);
}

int	shadow_cutter(t_env *e, t_obj *obj, t_obj *tmp, t_obj *light_obj)
{
	double	s;
	t_vc	p;
	t_vc	light;
	t_vc	v2;
	t_vc	inter;
	t_obj	*clst;

	v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
	clst = e->cut_link;
	while (clst)
	{
		if (tmp != obj && clst->id_cut == obj->id_obj)
		{
			light = vec_sub(v2, light_obj->pos);
			p = vec_sub(obj->pos, v2);
			s = distance_to_inter(e, obj, light, p);
			if (obj == tmp && obj->type != 6 && obj->type != 7)
				s = e->smax;
			inter = vec_sub(vec_add(vec_mult(light, -s), v2), clst->pos);
			if (s > 0.000001 && s < 0.99999 && vec_x(inter, clst->rot) > 0)
				return (0);
		}
	clst = clst->next;
	}
	return (1);
}

int		shadows(t_env *e, t_obj *tmp, t_obj *olst, t_obj *light_obj)
{

	while (olst)
	{
		if (is_not_cut(olst, e) && !shadow_no_cutter(e, olst, tmp, light_obj))
			return (0);
		if (!is_not_cut(olst, e) && !shadow_cutter(e, olst, tmp, light_obj))
			return (0);
		olst = olst->next;
	}
	return (1);
}

// int		shadows(t_env *e, t_obj *tmp, t_obj *olst, t_obj *light_obj)
// {
// 	double	s;
// 	t_vc	p;
//
// 	t_vc	light;
// 	t_vc	v2;
// 	while (olst)
// 	{
// 		v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
// 		light = vec_mult(e->lm, -1.0);
// 		if (tmp != olst)
// 		{
// 			light = vec_sub(v2, light_obj->pos);
// 			p = vec_sub(olst->pos, v2);
//             // On veut aue dst_to_inter nous donne lobjet et change dans la structure la valeur s
// 			s = distance_to_inter(e, olst, light, p);
// 			if (olst == tmp && olst->type != 6 && olst->type != 7)
// 				s = e->smax;
// 			if (s > 0.000001 && s < 0.99999)
// 				return (0);
// 		}
// 	olst = olst->next;
// 	}
// 	return (1);
// }
