/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/13 18:20:56 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc	create_ray(t_env *e)
{
	t_vc v;

	v.x = (double)(FOV);
	v.y = (double)(WINY / 2 - e->y);
	v.z = (double)(WINZ / 2 - e->z);
	rot_all_axis(&v, e->eye_rot);
	return (v);
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
		e->ray = create_ray(e);
		e->offset = vec_sub(e->eye_lookfrom, tmp->pos); // AJOUTER LA ROTATION DE L'OBJET + CAMERA
		if (tmp->type == 1)
			t = inter_sph(e, tmp, e->ray, e->offset);
		if (tmp->type == 2)
			t = inter_cyl(e, tmp, e->ray, e->offset);
		if (tmp->type == 3)
			t = inter_cone(e, tmp, e->ray, e->offset);
		if (tmp->type == 4)
			t = inter_plane(e->ray, e->offset);
		if (t > 0.00001 && t < e->t)
		{
			e->t = t;
			ret = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

double		shadow(t_env *e, t_obj *tmp)
{
	double	s;
	t_vc	p;
	t_vc	light;
	t_vc	v2;

	e->s = 999999999;
	v2= init_vc(e->eye_lookfrom.x + e->t * e->ray.x, e->eye_lookfrom.y + e->t * e->ray.y, e->eye_lookfrom.z + e->t * e->ray.z);
	p = vec_mult(vec_sub(tmp->pos, v2), 1.0);

	light = vec_mult(e->lm, 1.0);
	while (tmp)
	{
		if (tmp->type == 1)
			s = inter_sph(e, tmp, light, p);
		else if (tmp->type == 2)
			s = inter_cyl(e, tmp, light, p);
		else if (tmp->type == 3)
			s = inter_cone(e, tmp, light, p);
		else if (tmp->type == 4)
			s = inter_plane(light, p);
		if (s > 0.00001 && s < 0.99)
		{
			e->s = s;
		}

		tmp = tmp->next;
	}
	return (e->s);
}

int multiply_color(int *rgb, double mult)
{
	int hex;

	if (mult < 0)
		mult = 0;
		hex = (int)(mult * rgb[2]) + (int)(mult * rgb[1]) * 0X100 + (int)(mult * rgb[0]) * 0X100 * 0X100 ;
	return (hex);
}

void	scene_plot(t_env *e)
{
	t_obj	*o;
	t_obj	*tmp;
	double		s;
	int		i;

	o = e->link;
	e->z = -1;
	i = 0;
	s=0;
	while (++(e->z) < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			tmp = nearest_node(e, o);
			if (tmp)
			{

				lighting_vectors(e, tmp);
				if (e->y == 500 && e->z == 500)
				{
					printf("t %f\n", e->t);
					printf("e-v x %f y %f z %f \n", e->v.x, e->v.y, e->v.z);
					printf("ray-v x %f y %f z %f \n", e->ray.x, e->ray.y, e->ray.z);
				}
				e->cost = vec_dot(e->n, e->lm);
				s = shadow(e, tmp);
				if (e->y == 500 && e->z == 500)
				{
					printf("e-v x %f y %f z %f \n", e->v.x, e->v.y, e->v.z);
				}
				if (e->cost > 0 && s == 999999999)
					draw_point(e, e->y, e->z, rgb_to_hexa(tmp, e));
				else
					draw_point(e, e->y, e->z, 0x000000);

			}

		}
	}
}
