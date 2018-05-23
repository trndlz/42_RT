/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/23 10:58:11 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_raytracer(t_env *e, t_obj *tmp)
{
	e->offset = vec_sub(&e->eye, &tmp->pos);
	e->plan = init_vc(FOV, WINW / 2 - e->x, WINH / 2 - e->y);
	e->ray = vec_sub(&e->plan, &e->eye);
}

t_obj	*nearest_node(t_env *e, t_obj *tmp)
{
	double	t;
	t_obj	*ret;

	t = 0;
	e->t = 999999999;
	ret = NULL;
	while (tmp)
	{
		create_raytracer(e, tmp);
		if (tmp->type == 1)
			t = inter_sph(e, tmp);
		if (tmp->type == 2)
			t = inter_cyl(e, tmp);
		if (tmp->type == 3)
			t = inter_cone(e, tmp);
		if (tmp->type == 4)
			t = inter_plane(e, tmp);
		if (t > 0.00001 && t < e->t)
		{
			e->t = t;
			ret = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	scene_plot(t_env *e)
{
	t_obj	*o;
	t_obj	*tmp;

	o = e->link;
	e->y = -1;
	while (++(e->y) < WINH)
	{
		e->x = -1;
		while (++(e->x) < WINW)
		{
			tmp = nearest_node(e, o);

			if (tmp)
			{
				lighting_vectors(e, tmp);
				e->cost = vec_dot(&e->n, &e->lm);
				//if (tmp->type == 2)
					//printf("x %f y %f z %f\n", e->n.x, e->n.y, e->n.z);
				if (e->cost > 0.00001 && e->cost < 1.0)
					draw_point(e, e->x, e->y, rgb_to_hexa(tmp, e));
				else
					draw_point(e, e->x, e->y, 0);
			}
		}
	}
}
