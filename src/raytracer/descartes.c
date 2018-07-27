/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descartes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 13:55:25 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec	next_hit;
	double		r;

	r = (!(textures_coef(hit->hit_obj, hit, ray))) ? hit->hit_obj->descartes.y : 0;
	hit->nt--;
	next_hit = *hit;
	r_ray.direction = ray.direction;
	r_ray.origin = inter_position(ray, hit->t);
	r_ray.origin = vec_add(r_ray.origin, vec_mult(ray.direction, SHADOW_BIAS));
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray);
		new_color = add_color(multiply_color(new_color, r), multiply_color(old_color, (1 - r)));
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}

int		reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec 	next_hit;
	double		r;

	hit->nr--;
	next_hit = *hit;
	r = hit->hit_obj->descartes.x;
	r_ray.direction = vec_mult(vec_norm(ray.direction), -1);
	r_ray.direction = vec_sub(vec_mult(hit->n, 2 * vec_dot(r_ray.direction, hit->n)), r_ray.direction);
	r_ray.origin = hit->hit_inter;
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray);
		new_color = add_color(multiply_color(new_color, r), multiply_color(old_color, (1 - r)));
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}
