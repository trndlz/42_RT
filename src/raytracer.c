/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/12 19:15:00 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_raytracer(t_env *e, t_obj *tmp)
{
	e->offset = vec_sub(&e->eye_pos, &tmp->pos);
	e->plan = init_vc(FOV, WINX / 2 - e->x, WINY / 2 - e->y);
	e->ray = vec_sub(&e->plan, &e->eye_pos);
	vec_norm(&e->ray);
}

void		init_vport(t_env *e)
{
	t_vc	dir;
	t_vc	tmp_dist;
	t_vc	tmp_height;
	t_vc	tmp_width;

	e->vport->up = init_vc(0.0, 1.0, 0.0);
	e->vport->vp_dist = 1;
	e->vport->vp_height = 0.35;
	e->vport->vp_width = 0.5;
	dir = vec_sub(&e->eye_rot, &e->eye_pos);
	vec_norm(&dir);
	e->vport->right = vec_croise(&e->vport->up, &dir);
	e->vport->up = vec_croise(&dir, &e->vport->right);
	tmp_dist = vec_mult(&dir, e->vport->vp_dist);
	tmp_height = vec_mult(&e->vport->up, e->vport->vp_height / 2.0);
	tmp_width = vec_mult(&e->vport->right, e->vport->vp_width / 2.0);
	e->vport->vp_up_left = vec_add(&e->eye_pos, &tmp_dist);
	e->vport->vp_up_left = vec_add(&e->vport->vp_up_left, &tmp_height);
	e->vport->vp_up_left = vec_sub(&e->vport->vp_up_left, &tmp_width);
}

t_vc	create_ray(t_env *e)
{
	double	x_indent;
	double	y_indent;
	t_vc	right;
	t_vc	up;
	t_vc	vp_up_left;

	x_indent = e->vport->vp_width / WINX;
	y_indent = e->vport->vp_height / WINY;
	right = vec_mult(&e->vport->right, x_indent);
	right = vec_mult(&right, e->x);
	up = vec_mult(&e->vport->up, x_indent);
	up = vec_mult(&up, e->y);
	vp_up_left = vec_sub(&right, &up);
	vp_up_left = vec_add(&e->vport->vp_up_left, &vp_up_left);
	return (vec_sub(&vp_up_left, &e->eye_pos));
}

t_obj	*nearest_node(t_env *e, t_obj *tmp)
{
	double	t;
	t_obj	*ret;

	t = 0;
	e->t = 999999999;
	ret = NULL;
	//init_vport(e);
	while (tmp)
	{
		create_raytracer(e, tmp);
		//e->ray = create_ray(e);
		//vec_norm(&e->ray);
		//e->offset = vec_sub(&e->eye_pos, &tmp->pos);
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
	double	x;
	t_vc	dist;
	t_vc	p;
	t_vc	light;


	p = init_vc(e->eye_pos.x + e->t * e->ray.x, e->eye_pos.y + e->t * e->ray.y, e->eye_pos.z + e->t * e->ray.z);
	dist = vec_sub(&e->light->pos, &p);
	light = vec_sub(&e->light->pos, &tmp->pos);
	x = vec_mod(&dist);
	while (tmp)
	{
		if (tmp->type == 1)
			s = inter_sph(e, tmp, p, light);
		else if (tmp->type == 2)
			s = inter_cyl(e, tmp, light, p);
		else if (tmp->type == 3)
			s = inter_cone(e, tmp, light, p);
		else if (tmp->type == 4)
			s = inter_plane(tmp, light, p);
		// if (e->x == 514 && e->y == 262)
		// {
		// 	printf("TYPE %d : s %f / t %f \n", tmp->type, s, e->t);
		// 	printf("intersection x %f : y %f / z %f \n", p.x, p.y, p.z);
		// 	printf("ray x %f : y %f / z %f \n", e->ray.x, e->ray.y, e->ray.z);
		// 	printf("light x %f : y %f / z %f \n\n", light.x, light.y, light.z);
		// }
		if (s > 0.00001 && s < x)
		{
			//printf("x %d y %d ", e->x, e->y);
			return (1);
		}

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
				if (e->x == 525 && e->y == 401)
				{
					//printf("s %d / t %f \n", s, e->t);
				}
				if (s == 1)
					draw_point(e, e->x, e->y, 0x000000);
				else if (e->cost > 0.00001 && e->cost < 1.0)
					draw_point(e, e->x, e->y, rgb_to_hexa(tmp, e));
				else
					draw_point(e, e->x, e->y, 0x000000);

			}

		}
	}
}
