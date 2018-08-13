/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:43 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		get_minimum_tr(t_hit_rec hit_s, t_obj *olst, t_ray light_r)
{
	double	tr;
	double	t;
	double	tr_max;

	tr_max = 1;
	t = distance_to_inter(&hit_s, olst, light_r);
	if (t > D_ZERO && t < (1 - D_ZERO))
	{
		hit_s.hit_obj = olst;
		hit_s.t = hit_s.t1;
		hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
			? hit_s.hit_obj->descartes.y : 0;
		tr_max = (tr < tr_max) ? tr : tr_max;
	}
	if (hit_s.t2 > D_ZERO && hit_s.t2 < (1 - D_ZERO) && tr > 0)
	{
		hit_s.t = hit_s.t2;
		hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
		tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
			? hit_s.hit_obj->descartes.y : 0;
		tr_max = (tr < tr_max) ? tr : tr_max;
	}
	return (tr_max);
}

double		get_minimum_tr_cut(t_hit_rec hit_s, t_obj *olst, t_ray light_r)
{
	double	tr;
	double	tr_max;

	tr_max = 1;
	hit_s.t = INFINITY;
	if (hit_cut(&hit_s, olst, light_r))
	{
		if ((hit_s.t1 < (1 - D_ZERO) && hit_s.t1 > D_ZERO)
		|| (hit_s.t2 < (1 - D_ZERO) && hit_s.t2 > D_ZERO))
		{
			tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
				? hit_s.hit_obj->descartes.y : 0;
			tr_max = (tr < tr_max) ? tr : tr_max;
			if (hit_s.t2 > D_ZERO && hit_s.t2 < (1 - D_ZERO) && tr > 0.01)
			{
				hit_s.t = hit_s.t2;
				hit_s.n = normal_vectors(&hit_s, hit_s.hit_obj, light_r);
				tr = (!(textures_coef(hit_s.hit_obj, &hit_s, light_r)))
					? hit_s.hit_obj->descartes.y : 0;
				tr_max = (tr < tr_max) ? tr : tr_max;
			}
		}
	}
	return (tr_max);
}

double		shadow_calculation(t_env *e, t_ray light_r)
{
	t_hit_rec	hit_s;
	double		tr_max;
	double		tr;
	t_obj		*olst;

	tr_max = 1;
	tr = 1;
	olst = e->obj_link;
	hit_s.t2 = -1;
	while (olst)
	{
		if (!olst->cut)
		{
			tr = get_minimum_tr(hit_s, olst, light_r);
			tr_max = (tr < tr_max) ? tr : tr_max;
		}
		if (olst->cut)
		{
			tr = get_minimum_tr_cut(hit_s, olst, light_r);
			tr_max = (tr < tr_max) ? tr : tr_max;
		}
		olst = olst->next;
	}
	return (tr_max);
}

/*
** shadows() returns:
** tr coefficient of object between intersection and light
** 0 if object is opaque
** 1 if object is transparent or no intersection between object and light
*/

double		shadows(t_env *e, t_hit_rec *hit, t_obj *light_obj, t_ray ray)
{
	t_ray	light_r;

	light_r.origin = inter_position(ray, hit->t);
	light_r.direction = vec_sub(light_obj->pos, light_r.origin);
	return (shadow_calculation(e, light_r));
}
