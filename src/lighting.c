/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/13 15:09:19 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc	normal_cylinder(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc			normal_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	double	m;
	t_vc	n;
	t_vc	x;

	k = obj->size;
	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, (m + k)));
	return (vec_norm(n));
}

t_vc	normal_cone(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	m *= 1 + car(tan(M_PI * obj->size / 180));
	n = vec_sub(vec_add(vec_mult(ray.direction, hit->t), x), vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc	normal_vectors(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	if (obj->type == 4)
		return (normal_cylinder(hit, obj, ray));
	else if (obj->type == 5)
		return (normal_cone(hit, obj, ray));
	else if (obj->type == 6 || obj->type == 7)
		return (vec_norm(obj->rot));
	else if (obj->type == 8)
		return (normal_paraboloid(hit, obj, ray));
	else
		return (vec_norm(vec_sub(inter_position(ray, hit->t), obj->pos)));
}

int	shadow_cutter(t_env *e, t_obj *obj, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	double	s;
	t_vc	p;
	t_vc	light;
	t_vc	v2;
	t_vc	inter;
	t_obj	*clst;

	v2 = vec_add(vec_mult(ray.direction, hit->t), ray.origin);
	clst = e->cut_link;
	while (clst)
	{
		if (hit->hit_obj != obj && clst->id_cut == obj->id_obj)
		{
			light = vec_sub(v2, light_obj->pos);
			p = vec_sub(obj->pos, v2);
			s = distance_to_inter(hit, obj, light, p);
			if (obj == hit->hit_obj && obj->type != 6 && obj->type != 7)
				s = hit->smax;
			inter = vec_sub(vec_add(vec_mult(light, -s), v2), clst->pos);
			if (s > 0.000001 && s < 0.99999 && vec_x(inter, clst->rot) > 0)
				return (0);
		}
	clst = clst->next;
	}
	return (1);
}

int	shadow_no_cutter(t_obj *obj, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	double	s;
	t_vc	p;
	t_vc	light;
	t_vc	v2;
	t_vc	inter;

	v2 = vec_add(vec_mult(ray.direction, hit->t), ray.origin);
	if (hit->hit_obj != obj)
	{
		light = vec_sub(v2, light_obj->pos);
		p = vec_sub(obj->pos, v2);
		s = distance_to_inter(hit, obj, light, p);
		inter = vec_add(vec_mult(light, s), light_obj->pos);
		if (obj == hit->hit_obj && obj->type != 6 && obj->type != 7)
			s = hit->smax;
		if (s > 0.000001 && s < 0.99999)
			return (0);
	}
	return (1);
}


int		shadows(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_obj *olst;

	olst = e->obj_link;
	while (olst)
	{
		if (is_not_cut(olst, e) && !shadow_no_cutter(olst, hit, light_obj, ray))
			return (0);
		if (!is_not_cut(olst, e) && !shadow_cutter(e, olst, hit, light_obj, ray))
			return (0);
		olst = olst->next;
	}
	return (1);
}
