/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/26 19:12:19 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_obj_color(t_hit_rec *hit, t_ray ray)
{
	if (hit->hit_obj->o_type == SPHERE && hit->hit_obj->texture == EARTH)
		return (get_texture_sphere(hit, ray));
	else
		return (hit->hit_obj->col);
}

int			specular_diffuse(t_obj *light, t_hit_rec *hit, t_ray ray)
{
	int		color_diff;
	int		color_spec;
	double	dot_spec;
	double	dot_diff;
	t_vc	rm;

	rm = vec_norm(vec_sub(vec_mult(hit->n, 2 * hit->cost), hit->lm));
	dot_spec = ratio_limits(pow(vec_dot(rm, vec_norm(vec_mult(hit->v, -1.0))),
		ALPHA_SPEC));
	dot_diff = ratio_limits(hit->cost);
	color_spec = multiply_color(light->col, dot_spec * hit->hit_obj->phong.x);
	color_diff = multiply_color(get_obj_color(hit, ray), dot_diff * hit->hit_obj->phong.y);
	color_spec = add_color(color_spec, color_diff);
	return (color_spec);
}

void	perturb_norm(t_hit_rec *hit)
{
	if (hit->hit_obj->perturb == 0)
		return;
	else if (hit->hit_obj->perturb == 1)
	{
		hit->n.z += 0.1 * tan(0.05 * hit->hit_inter.y);
		hit->n.z += 0.1 * tan(0.05 * hit->hit_inter.z);
	}
	else if (hit->hit_obj->perturb == 2)
		hit->n.z += 0.3 * sin(0.05 * hit->hit_inter.z);
	else if (hit->hit_obj->perturb == 3)
	{
		hit->n.z += 0.1 * tan(0.1 * hit->hit_inter.y);
		hit->n.z += 0.1 * tan(0.1 * hit->hit_inter.z);
	}
	else if (hit->hit_obj->perturb == 4)
		hit->n.z += 0.2 * sin(0.8 * hit->hit_inter.z);
	else
		return;
	hit->n = vec_norm(hit->n);
	return;
}

int		phong_lighting(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*llst;
	int		color;
	double	s;

	llst = e->light_link;
	hit->n = normal_vectors(hit, hit->hit_obj, ray);
	perturb_norm(hit);
	hit->v = inter_position(ray, hit->t);
	color = multiply_color(get_obj_color(hit, ray), hit->hit_obj->phong.z);
	while (llst)
	{
		s = shadows(e, hit, llst, ray);
		hit->lm = vec_norm(vec_sub(llst->pos, hit->v));
		hit->cost = vec_dot(hit->n, hit->lm);
		color = add_color(multiply_color(specular_diffuse(llst, hit, ray), s), color);
		llst = llst->next;
	}
	if (!(textures_coef(hit->hit_obj, hit, ray)))
		color = multiply_color(color, 0.6);
	return (color);
}
