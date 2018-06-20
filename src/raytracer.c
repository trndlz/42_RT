/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 16:19:10 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc	create_ray(t_env *e)
{
	t_vc v;

	v.x = (double)(FOV);
	v.y = (double)(WINY / 2 - e->y);
	v.z = (double)(WINZ / 2 - e->z);
	v = rot_all_axis(v, e->eye_rot);
	return (v);
}

double	distance_to_inter(t_env *e, t_obj *obj_list, t_vc ray, t_vc p)
{
	if (obj_list->type == 1)
		return (inter_sph(e, obj_list, ray, p));
	else if (obj_list->type == 2)
		return (inter_cyl(e, obj_list, ray, p));
	else if (obj_list->type == 3)
		return (inter_cone(e, obj_list, ray, p));
	else if (obj_list->type == 4)
		return (inter_plane(ray, p, obj_list));
	return (-1);
}

t_obj	*nearest_node(t_env *e)
{
	double	t;
	t_obj	*ret;
	t_obj	*olst;

	e->t = 999999999;
	ret = NULL;
	olst = e->obj_link;
	while (olst)
	{
		e->ray = create_ray(e);
		e->offset = vec_sub(e->eye_lookfrom, olst->pos);
		t = distance_to_inter(e, olst, e->ray, e->offset);
		if (t > 0.00001 && t < e->t)
		{
			e->t = t;
			ret = olst;
		}
		olst = olst->next;
	}
	return (ret);
}

void	compute_scene_vectors(t_env *e, t_obj *tmp)
{
	t_obj	*llst;
	int		color;
	int		nb_shadow;

	llst = e->light_link;
    // on met l'ambiant, on peut multiplier par le nmbre de light
	color = multiply_color(tmp->col, tmp->coef.z);
	draw_point(e, e->y, e->z, color);
	while (llst)
	{
		normal_vectors(e, tmp);
		e->v2 = vec_add(vec_add(vec_mult(e->ray, e->t), e->offset), tmp->pos);
		e->lm = vec_norm(vec_sub(llst->pos, e->v2));
		e->cost = vec_dot(e->n, e->lm);
		nb_shadow = shadows(e, tmp, e->obj_link, llst);
		if (nb_shadow)
			color = specular_diffuse(color, llst, tmp, e);
		draw_point(e, e->y, e->z, color);
		llst = llst->next;
	}
}

void	*scene_plot(void *arg)
{
	t_obj	*tmp;
	t_env	*e;

	e = (t_env *)arg;
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			e->ray = create_ray(e);
			tmp = nearest_node(e);
			if (tmp)
			{
				e->offset = vec_sub(e->eye_lookfrom, tmp->pos);
				compute_scene_vectors(e, tmp);
			}
		}
	}
	return (NULL);
}
