/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/25 18:14:44 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_raytracer(t_env *e, t_obj *tmp)
{
	e->offset = vec_sub(&e->eye, &tmp->pos);
	e->plan = init_vc(FOV, WINX / 2 - e->x, WINY / 2 - e->y);
	e->ray = vec_sub(&e->plan, &e->eye);
	vec_norm(&e->ray);
}



void	create_raytracer2(t_env *e, t_obj *obj)
{
	double	u;
	double	v;
	t_vc	i;
	t_vc	j;
	t_vc	k;

	u = (WINX - (double)e->x * 2.0) / WINX;
	v = (WINY - (double)e->y * 2.0) / WINY;
	k = vec_sub(&e->eye_dir, &e->eye);
	vec_norm(&k);
	i = vec_croise(&k, &(t_vc){0.0, 1.0, 0.0});
	vec_norm(&i);
	j = vec_croise(&i, &k);
	e->ray = (t_vc){u * i.x + v * j.x + FOV * k.x,
		u * i.y + v * j.y + FOV * k.y,
		u * i.z + v * j.z + FOV * k.z};
	vec_norm(&e->ray);
	e->offset = vec_sub(&e->eye, &obj->pos);
}

void	create_shadow_ray(t_env *e, t_obj *tmp)
{
	e->offset = vec_sub(&e->v, &tmp->pos);
	e->ray = e->lm;
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
		//create_raytracer2(e, tmp);
		if (tmp->type == 1)
			t = inter_sph(e, tmp, e->ray, e->offset);
		if (tmp->type == 2)
			t = inter_cyl(e, tmp, e->ray, e->offset);
		if (tmp->type == 3)
			t = inter_cone(e, tmp, e->ray, e->offset);
		if (tmp->type == 4)
			t = inter_plane(tmp, e->ray, e->offset);
		if (t > 0.00001 && t < e->t)
		{
			e->t = t;
			ret = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int		shadow(t_env *e, t_obj *tmp)
{
	double	s;
	t_vc	p;
	t_vc	light;

	p = init_vc(e->eye.x + e->t * e->ray.x, e->eye.y + e->t * e->ray.y, e->eye.z + e->t * e->ray.z);
	light = vec_sub(&e->light->pos, &tmp->pos);
	//light = init_vc(1, 1, 1);
	while (tmp)
	{
		if (tmp->type == 1)
			s = inter_sph(e, tmp, light, p);
		if (tmp->type == 2)
			s = inter_cyl(e, tmp, light, p);
		if (tmp->type == 3)
			s = inter_cone(e, tmp, light, p);
		if (tmp->type == 4)
			s = inter_plane(tmp, light, p);
		if (s > 0.00001 && s < 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	scene_plot(t_env *e)
{
	t_obj	*o;
	t_obj	*tmp;
	int		s;
	int		i;

	o = e->link;
	e->y = -1;
	i = 0;
	while (++(e->y) < WINY)
	{
		e->x = -1;
		while (++(e->x) < WINX)
		{
			tmp = nearest_node(e, o);
			if (tmp)
			{
				lighting_vectors(e, tmp);
				e->cost = vec_dot(&e->n, &e->lm);
				s = shadow(e, tmp);
				if (s > 0)
					draw_point(e, e->x, e->y, 0x000000);
				else if (e->cost > 0.00001 && e->cost < 1.0)
					draw_point(e, e->x, e->y, rgb_to_hexa(tmp, e));
				else
					draw_point(e, e->x, e->y, 0x000000);

			}

		}
	}
}
