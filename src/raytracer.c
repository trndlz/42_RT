/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 18:24:54 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	create_ray(int y, int z, t_vc eye_rot, t_vc ray_origin)
{
	t_ray ray;

	ray.direction.x = (double)(FOV);
	ray.direction.y = (double)(WINY / 2 - y);
	ray.direction.z = (double)(WINZ / 2 - z);
	ray.direction = rot_all_axis(ray.direction, eye_rot);
	ray.origin = ray_origin;
	return (ray);
}

int			specular_diffuse(int color, t_obj *light, t_obj *obj, t_hit_rec *hit, t_ray ray)
{
	int		color_diff;
	int		color_spec;
	double	dot_spec;
	double	dot_diff;
	t_vc	rm;

	rm = vec_norm(vec_sub(vec_mult(hit->n, 2 * hit->cost), hit->lm));
	dot_spec = ratio_limits(pow(vec_dot(rm, vec_norm(vec_mult(hit->v2, -1.0))),
		ALPHA_SPEC));
	dot_diff = ratio_limits(hit->cost);
	color_spec = multiply_color(light->col, dot_spec * obj->coef.x);
	color_diff = multiply_color(obj->col, dot_diff * obj->coef.y);
	if (!textures_coef(obj, hit, ray))
		color_diff = multiply_color(color_diff, 0.6);
	color_spec = add_color(add_color(color_spec, color_diff), color);
	return (color_spec);
}

double	distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_vc ray, t_vc p)
{
	double d;

	d = -1.0;
	d = (obj_list->type == 3) ? inter_sph(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 4) ? inter_cyl(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 5) ? inter_cone(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 6) ? inter_plane(ray, p, obj_list) : d;
	d = (obj_list->type == 8) ? inter_paraboloid(hit, obj_list, ray, p) : d;
	return (d);
}

int		is_not_cut(t_obj *obj, t_env *e)
{
	t_obj *cut;

	cut = e->cut_link;
	while (cut)
	{
		if (cut->id_cut == obj->id_obj)
			return (0);
		cut = cut->next;
	}
	return (1);
}

char	hit_not_cut(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	t;
	t_vc	offset;
	char	hit_anything;

	hit_anything = 0;
	offset = vec_sub(ray.origin, obj->pos);
	t = distance_to_inter(hit, obj, ray.direction, offset);
	if (t > 0.000001 && t < hit->t)
	{
		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	return (hit_anything);
}

char	hit_cut(t_hit_rec *hit, t_env *e, t_obj *obj, t_ray ray)
{
	t_obj	*clst;
	double	t;
	double	t_cut;
	t_vc	inter;
	char	hit_anything;

	hit_anything = 0;
	clst = e->cut_link;
	while (clst)
	{
		if (clst->id_cut == obj->id_obj)
		{
			t_cut = distance_to_inter(hit, clst, ray.direction,
				vec_sub(ray.origin, clst->pos));
			t = distance_to_inter(hit, obj, ray.direction,
				vec_sub(ray.origin, obj->pos));
			inter = vec_sub(vec_add(vec_mult(ray.direction, t),
				ray.origin), clst->pos);
			if (t > 0 && t < hit->t && vec_x(inter, clst->rot) > 0)
			{
				hit->t = t;
				hit->hit_obj = obj;
				hit_anything = 1;
			}
			if (t > 0 && t_cut < hit->t && hit->t1 < t_cut && hit->t2 > t_cut)
			{
				hit->t = t_cut;
				hit->hit_obj = clst;
				hit_anything = 1;
			}
		}
		clst = clst->next;
	}
	return (hit_anything);
}

char		nearest_node(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	olst = e->obj_link;
	while (olst)
	{
		if (is_not_cut(olst, e))
		{
			if (hit_not_cut(hit, olst, ray))
				hit_anything = 1;
		}
		else
		{
			if (hit_cut(hit, e, olst, ray))
				hit_anything = 1;
		}
		olst = olst->next;
	}

	return (hit_anything);
}

int		phong_lighting(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*llst;
	int		color;
	int		is_lit;

	llst = e->light_link;
	color = multiply_color(hit->hit_obj->col, hit->hit_obj->coef.z);
	if (!(textures_coef(hit->hit_obj, hit, ray)))
		color = multiply_color(color, 0.6);
	while (llst)
	{
		hit->n = normal_vectors(hit, hit->hit_obj, ray);
		hit->v2 = vec_add(vec_mult(ray.direction, hit->t), ray.origin);
		hit->lm = vec_norm(vec_sub(llst->pos, hit->v2));
		hit->cost = vec_dot(hit->n, hit->lm);
		is_lit = shadows(e, hit, llst, ray);
		// if (is_lit)
			color = specular_diffuse(color, llst, hit->hit_obj, hit, ray);
		llst = llst->next;
	}
	return (color);
}

int		recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit);
int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray);

int		transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec 	next_hit;
	double		r;

	r = (!(textures_coef(hit->hit_obj, hit, ray))) ? hit->hit_obj->tr : 0;
	next_hit = *hit;
	next_hit.nt = hit->nt;
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

int		recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec 	next_hit;
	double		r;

	next_hit = *hit;
	next_hit.nr = hit->nr;
	r = hit->hit_obj->r;
	r_ray.direction = vec_mult(vec_norm(ray.direction), -1);
	r_ray.direction = vec_sub(vec_mult(hit->n, 2 * vec_dot(r_ray.direction, hit->n)), r_ray.direction);
	r_ray.origin = hit->hit_inter;
	if (nearest_node(e, r_ray, &next_hit))
	{
		new_color = compute_point(e, &next_hit, r_ray);
		new_color = add_color(multiply_color(new_color, r), multiply_color(old_color, (1 - r)));
		return (new_color);
	}
	return (multiply_color(old_color, r));
}

int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray)
{
	int	pixel;

	hit->hit_inter = inter_position(ray, hit->t);
	pixel = phong_lighting(e, ray, hit);
	if (hit->hit_obj->tr > 0 && hit->nt > 0)
		pixel = transparency(e, pixel, ray, hit);
	else if (hit->hit_obj->r > 0 && hit->nr > 0)
		pixel = recursive_reflection(e, pixel, ray, hit);
	return (pixel);
}

void	*scene_plot(void *arg)
{
	t_env		*e;
	int			px_color;
	t_ray		ray;
	t_hit_rec	hit_rec;

	e = (t_env *)arg;
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			hit_rec.nr = 1;
			hit_rec.nt = 56;
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				px_color = compute_point(e, &hit_rec, ray);
				draw_point(e, e->y, e->z, px_color);
			}
		}
	}
	// antialias(e);
	// global_filter(e, 2);
	// stereoscopic(e);
	return (NULL);
}
