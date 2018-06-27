/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:26:30 by jostraye          #+#    #+#             */
/*   Updated: 2018/06/26 16:16:05 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	aa_create_ray(t_env *e, double offy, double offz)
{
	e->ray.x = (double)(FOV);
	e->ray.y = (double)(WINY / 2 - e->y) - offy;
	e->ray.z = (double)(WINZ / 2 - e->z) - offz;
	e->ray = rot_all_axis(e->ray, e->eye_rot);
}

void		aa_draw_point(t_env *e, unsigned int color)
{
	int i;
	double aa_color;
	i = (e->y + ((e->z * e->s_l) / 4));
	aa_color = multiply_color(color, 0.25);
	if (i >= 0 && i < (WINY * WINZ))
		e->imgstr[i] = add_color(aa_color, e->imgstr[i]);
}

void	aa_compute_scene_vectors(t_env *e, t_obj *tmp)
{
	t_obj	*llst;
	int		color;
	int		is_lit;

	llst = e->light_link;
	color = multiply_color(tmp->col, tmp->coef.z);
	aa_draw_point(e, color);
	while (llst)
	{
		normal_vectors(e, tmp);
		e->v2 = vec_add(vec_add(vec_mult(e->ray, e->t), e->offset), tmp->pos);
		e->lm = vec_norm(vec_sub(llst->pos, e->v2));
		e->cost = vec_dot(e->n, e->lm);
		is_lit = shadows(e, tmp, e->obj_link, llst);
		if (is_lit)
		{
			color = specular_diffuse(color, llst, tmp, e);
			aa_draw_point(e, color);
		}
		else
			aa_draw_point(e, 0X000000);

		llst = llst->next;
	}
}

void	antialias(t_env *e)
{
	t_obj	*tmp;
	double offy;
	double offz;
	int i;

	e->z = ((e->thread_int) * WINZ / TH_NB - 1);
	while (++(e->z) < (((e->thread_int + 1) * WINZ) / TH_NB))
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			i = (e->y + ((e->z * e->s_l) / 4));
			e->imgstr[i] = 0;
			offy = 0;
			offz = 0;
			while (offy + offz < 1.5)
			{
				aa_create_ray(e, offy, offz);
				tmp = nearest_node(e);
				if (tmp)
				{
					e->offset = vec_sub(e->eye_lookfrom, tmp->pos);
					aa_compute_scene_vectors(e, tmp);
				}
				if (e->y == 500 && e->z == 500)
				printf("y %fz %f\n",offy, offz);
				if (offy == 0 && offz == 0)
					offy = 0.5;
				else if (offy == 0.5 && offz == 0)
				{
					offz = 0.5;
					offy = 0;
				}
				else
					offy += 0.5;
			}
		}
	}
}
