/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/17 19:01:08 by jostraye         ###   ########.fr       */
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

double	distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_vc ray, t_vc p)
{
	double d;

	d = -1.0;
	d = (obj_list->type == 3) ? inter_sph(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 4) ? inter_cyl(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 5) ? inter_cone(hit, obj_list, ray, p) : d;
	d = (obj_list->type == 6) ? inter_plane(hit, ray, p, obj_list) : d;
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

char ft_isbetween(double a, double b, double c)
{
	if ((a < c && a > b) || (a > c && a < b))
		return (1);
	else
		return (0);
}

char	hit_hole_plane(t_hit_rec *hit, t_obj *clst, t_obj *obj, t_ray ray)
{
		char hit_anything;
		t_hit_rec cut;

		cut.nr = 1;
		hit_anything = 0;
		distance_to_inter(&cut, clst, ray.direction,	vec_sub(ray.origin, clst->pos));
		distance_to_inter(hit, obj, ray.direction, vec_sub(ray.origin, obj->pos));
		if (hit->t1 > 0 && !ft_isbetween(hit->t1, cut.t1, cut.t2))
		{
			hit->t = hit->t1;
			hit->hit_obj = obj;
			hit_anything = 1;
		}
		return (hit_anything);
}

char	hit_cut_plane(t_hit_rec *hit, t_obj *clst, t_obj *obj, t_ray ray)
{
	char hit_anything;
	double	t_cut;
	double	t;
	t_vc	inter;

	hit_anything = 0;
	t_cut = distance_to_inter(hit, clst, ray.direction,	vec_sub(ray.origin, clst->pos));
	t = distance_to_inter(hit, obj, ray.direction, vec_sub(ray.origin, obj->pos));
	inter = vec_sub(vec_add(vec_mult(ray.direction, t), ray.origin), clst->pos);
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
	return (hit_anything);
}

char	hit_cut(t_hit_rec *hit, t_env *e, t_obj *obj, t_ray ray)
{
	t_obj	*clst;
	char	hit_anything;

	hit_anything = 0;
	clst = e->cut_link;
	while (clst)
	{
		if (clst->id_cut == obj->id_obj)
		{
			if (clst->type == 6)
				hit_anything = hit_cut_plane(hit, clst, obj, ray);
			else if (clst->type == 3 && obj->type == 6)
				hit_anything = hit_hole_plane(hit, clst, obj, ray);
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
	hit->t = 999999999;
	olst = e->obj_link;
	while (olst)
	{
		if (is_not_cut(olst, e) && hit_not_cut(hit, olst, ray))
			hit_anything = 1;
		else if (hit_cut(hit, e, olst, ray))
				hit_anything = 1;
		olst = olst->next;
	}
	return (hit_anything);
}



char	second_nearest_node(t_env *e, t_ray ray, t_hit_rec *hit, t_hit_rec *new_origin)
{
	t_obj	*olst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = 999999999;
	olst = e->obj_link;
	while (olst)
	{
		if (olst != new_origin->hit_obj)
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
		}
		olst = olst->next;
	}
	return (hit_anything);
}

int		transparency(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	t_hit_rec	*new_origin;
	double		tr;

	new_origin = hit;
	tr = hit->hit_obj->tr;
	r_ray = ray;
	r_ray.direction = vec_sub(new_origin->hit_inter, ray.origin);
	r_ray.origin = vec_sub(new_origin->hit_inter,
		vec_mult(new_origin->n, SHADOW_BIAS));
	if (second_nearest_node(e, r_ray, hit, new_origin))
	{
		new_color = compute_pixel_color(e, r_ray, hit);
		// if (hit->hit_obj->tr > 0)
		// 	new_color = transparency(e, new_color, r_ray, hit);
		new_color = add_color(new_color, old_color);
		return (new_color);
	}
	return (old_color);
}

int		compute_pixel_color(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*llst;
	int		color;
	int		is_lit;

	llst = e->light_link;
	if (hit->hit_obj->type == 3 && SPHERE_TEXTURE == 1)
		color = multiply_color(get_texture_sphere(hit, ray),
		hit->hit_obj->coef.z);
	else if (hit->hit_obj->type == 6 && PLANE_CHECKERS == 1)
		color = multiply_color(checkerboard_plane(hit, ray),
		hit->hit_obj->coef.z);
	else
		color = multiply_color(hit->hit_obj->col, hit->hit_obj->coef.z);
	while (llst)
	{
		hit->n = normal_vectors(hit, hit->hit_obj, ray);
		hit->v2 = vec_add(vec_mult(ray.direction, hit->t), ray.origin);
		hit->lm = vec_norm(vec_sub(llst->pos, hit->v2));
		hit->cost = vec_dot(hit->n, hit->lm);
		is_lit = shadows(e, hit, llst, ray);
		if (is_lit)
			color = specular_diffuse(color, llst, hit->hit_obj, hit, ray);
		llst = llst->next;
	}
	if (hit->hit_obj->tr > 0)
		color = multiply_color(color, (1 - hit->hit_obj->tr));
	if(e->z == 579 && e->y == 511)
	printf("c %f\n",hit->hit_obj->tr);
	return (color);
}

int		recursive_reflection(t_env *e, int old_color, t_ray ray, t_hit_rec *hit)
{
	t_ray		r_ray;
	int			new_color;
	double		r;

	if (hit->nr > 0)
	{
		r = hit->hit_obj->r;
		r_ray.direction = vec_mult(vec_norm(ray.direction), -1);
		r_ray.direction = vec_sub(vec_mult(hit->n, 2 *
			vec_dot(r_ray.direction, hit->n)), r_ray.direction);
		r_ray.origin = vec_add(vec_mult(ray.direction, hit->t), ray.origin);
		if (nearest_node(e, r_ray, hit))
		{
			new_color = compute_pixel_color(e, r_ray, hit);
			new_color = add_color(multiply_color(new_color, r),
			multiply_color(old_color, (1 - r)));
			hit->nr--;
			if (hit->nr)
				new_color = recursive_reflection(e, new_color, r_ray, hit);
			return (new_color);
		}
	}
	return (old_color);
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
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				hit_rec.hit_inter = vec_add(vec_mult(ray.direction,
					hit_rec.t), ray.origin);
				px_color = compute_pixel_color(e, ray, &hit_rec);
				if (hit_rec.hit_obj->r > 0)
					px_color = recursive_reflection(e, px_color, ray, &hit_rec);
				if (hit_rec.hit_obj->tr > 0)
					px_color = transparency(e, px_color, ray, &hit_rec);
				draw_point(e, e->y, e->z, px_color);
			}
		}
	}
	antialias(e);
	// global_filter(e, 2);
	// stereoscopic(e);
	return (NULL);
}
