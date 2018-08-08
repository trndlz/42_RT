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

static void		refraction(t_ray *ray, t_hit_rec *hit)
{
	double	cost;
	double	k;
	double	n;
	t_vc	norm;

	norm = vec_norm(hit->n);
	cost = vec_dot(norm, ray->direction);
	if (cost > 0)
	{
		n = hit->hit_obj->descartes.z;
		norm = vec_mult(norm, -1);
	}
	else
	{
		n = 1 / hit->hit_obj->descartes.z;
		cost = -cost;
	}
	k = n * n * (1.0 - cost * cost);
	ray->direction = vec_add(vec_mult(ray->direction, n),
	vec_mult(norm, (n * cost - sqrtf(1.0 - k))));
}

int				transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec	next_hit;
	double		r;

	r = (!(textures_coef(hit->hit_obj, hit, ray)))
		? hit->hit_obj->descartes.y : 0;
	e->nt--;
	next_hit = *hit;
	r_ray.direction = vec_norm(ray.direction);
	r_ray.origin = inter_position(ray, hit->t);
	r_ray.origin = vec_add(r_ray.origin, vec_mult(ray.direction, SHADOW_BIAS));
	if (hit->hit_obj->descartes.z > 1.0)
		refraction(&r_ray, hit);
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray, 0);
		new_color = mix_colors(new_color, old_color, r);
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}

int				reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec	next_hit;
	double		r;

	e->nr--;
	next_hit = *hit;
	r = hit->hit_obj->descartes.x;
	r_ray.direction = vec_mult(vec_norm(ray.direction), -1);
	r_ray.direction = vec_sub(vec_mult(hit->n, 2
				* vec_dot(r_ray.direction, hit->n)), r_ray.direction);
	r_ray.origin = hit->hit_inter;
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray, 1);
		new_color = mix_colors(new_color, old_color, r);
		return (new_color);
	}
	return (multiply_color(old_color, (1 - r)));
}
