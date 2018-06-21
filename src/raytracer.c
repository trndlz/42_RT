/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/21 12:12:03 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_ray(t_env *e)
{
	e->ray.x = (double)(FOV);
	e->ray.y = (double)(WINY / 2 - e->y);
	e->ray.z = (double)(WINZ / 2 - e->z);
	e->ray = rot_all_axis(e->ray, e->eye_rot);
}

double	distance_to_inter(t_env *e, t_obj *obj_list, t_vc ray, t_vc p)
{
	double d;

	d = (obj_list->type == 1) ? inter_sph(e, obj_list, ray, p) : -1.0;
	d = (obj_list->type == 2) ? inter_cyl(e, obj_list, ray, p) : d;
	d = (obj_list->type == 3) ? inter_cone(e, obj_list, ray, p) : d;
	d = (obj_list->type == 4) ? inter_plane(ray, p, obj_list) : d;
	return (d);
}

t_obj	*nearest_node(t_env *e)
{
	double	t;
	t_obj	*near_node;
	t_obj	*olst;

	e->t = 999999999;
	near_node = NULL;
	olst = e->obj_link;
	while (olst)
	{
		e->offset = vec_sub(e->eye_lookfrom, olst->pos);
		t = distance_to_inter(e, olst, e->ray, e->offset);
		if (t > 0 && t < e->t)
		{
			e->t = t;
			near_node = olst;
		}
		olst = olst->next;
	}
	return (near_node);
}

void	compute_scene_vectors(t_env *e, t_obj *tmp)
{
	t_obj	*llst;
	int		color;
	int		is_lit;

	llst = e->light_link;
	color = multiply_color(tmp->col, tmp->coef.z);
	draw_point(e, e->y, e->z, color);
	while (llst)
	{
		normal_vectors(e, tmp);
		e->v2 = vec_add(vec_add(vec_mult(e->ray, e->t), e->offset), tmp->pos);
		e->lm = vec_norm(vec_sub(llst->pos, e->v2));
		e->cost = vec_dot(e->n, e->lm);
		is_lit = shadows(e, tmp, e->obj_link, llst);
		if (is_lit)
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
			create_ray(e);
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
