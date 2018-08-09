/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 14:42:10 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_ray ray)
{
	double d;

	d = -1.0;
<<<<<<< HEAD
=======
	if (obj_list->o_type == LIGHT)
>>>>>>> b8be3718c5b0ca9eea99788f564ea73555968a62
	d = (obj_list->o_type == LIGHT) ? inter_sph(hit, obj_list, ray) : d;
	d = (obj_list->o_type == SPHERE) ? inter_sph(hit, obj_list, ray) : d;
	d = (obj_list->o_type == CYLINDER) ? inter_cyl(hit, obj_list, ray) : d;
	d = (obj_list->o_type == CONE) ? inter_cone(hit, obj_list, ray) : d;
	d = (obj_list->o_type == PLANE) ? inter_plane(ray, obj_list) : d;
	d = (obj_list->o_type == PARABOLOID)
		? inter_paraboloid(hit, obj_list, ray) : d;
	return (d);
}

char	hit_not_cut(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	t;
	char	hit_anything;

	hit_anything = 0;
	t = distance_to_inter(hit, obj, ray);
	if (t > D_ZERO && t < hit->t)
	{
		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	return (hit_anything);
}

char	hit_cut(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	t_obj	*clst;
	double	t;
	double	t_cut;
	t_vc	inter;
	char	hit_anything;

	hit_anything = 0;
	clst = obj->cut;
	t_cut = distance_to_inter(hit, clst, ray);
	t = distance_to_inter(hit, obj, ray);
	inter = vec_sub(vec_add(vec_mult(ray.direction, t), ray.origin), clst->pos);
	if (t > D_ZERO && t < hit->t && vec_x(inter, clst->rot) > D_ZERO)
	{
		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	else if (t > D_ZERO && t_cut < hit->t
		&& hit->t1 < t_cut && hit->t2 > t_cut && t_cut > D_ZERO)
	{
		hit->t = t_cut;
		hit->hit_obj = clst;
		hit_anything = 1;
	}
	return (hit_anything);
}

char	nearest_node(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	hit->t1 = -1;
	hit->t2 = -1;
	olst = e->obj_link;
	while (olst)
	{
		if (!olst->cut)
		{
			if (hit_not_cut(hit, olst, ray))
				hit_anything = 1;
		}
		else
		{
			if (hit_cut(hit, olst, ray))
				hit_anything = 1;
		}
		olst = olst->next;
	}
	return (hit_anything);
}
