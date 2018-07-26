/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/26 19:12:19 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		create_ray(int y, int z, t_vc eye_rot, t_vc ray_origin)
{
	t_ray ray;

	ray.direction.x = (double)(FOV);
	ray.direction.y = (double)(WINY / 2 - y);
	ray.direction.z = (double)(WINZ / 2 - z);
	ray.direction = rot_all_axis(ray.direction, eye_rot);
	ray.origin = ray_origin;
	return (ray);
}

int			specular_diffuse(t_obj *light, t_hit_rec *hit)
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
	color_spec = multiply_color(light->col, dot_spec * hit->hit_obj->coef.x);
	color_diff = multiply_color(hit->hit_obj->col, dot_diff * hit->hit_obj->coef.y);
	color_spec = add_color(color_spec, color_diff);
	return (color_spec);
}

double		distance_to_inter(t_hit_rec *hit, t_obj *obj_list, t_ray ray)
{
	double d;

	d = -1.0;
	d = (obj_list->o_type == SPHERE) ? inter_sph(hit, obj_list, ray) : d;
	d = (obj_list->o_type == CYLINDER) ? inter_cyl(hit, obj_list, ray) : d;
	d = (obj_list->o_type == CONE) ? inter_cone(hit, obj_list, ray) : d;
	d = (obj_list->o_type == PLANE) ? inter_plane(ray, obj_list) : d;
	d = (obj_list->o_type == PARABOLOID) ? inter_paraboloid(hit, obj_list, ray) : d;
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
	char	hit_anything;

	hit_anything = 0;
	t = distance_to_inter(hit, obj, ray);
	if (t > D_ZERO && t < hit->t)
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
	clst = get_cutter(e, obj);
	t_cut = distance_to_inter(hit, clst, ray);
	t = distance_to_inter(hit, obj, ray);
	inter = vec_sub(vec_add(vec_mult(ray.direction, t), ray.origin), clst->pos);
	if (t > D_ZERO && t < hit->t && vec_x(inter, clst->rot) > D_ZERO)
	{

		hit->t = t;
		hit->hit_obj = obj;
		hit_anything = 1;
	}
	else if (t > D_ZERO && t_cut < hit->t && hit->t1 < t_cut && hit->t2 > t_cut && t_cut > D_ZERO)
	{
		hit->t = t_cut;
		hit->hit_obj = clst;
		hit_anything = 1;
	}
	return (hit_anything);
}

char		nearest_node(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	t_obj	*llst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	hit->t1 = -1;
	hit->t2 = -1;
	olst = e->obj_link;
	llst = e->light_link;
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
	// while (llst)
	// {
	// 		if (hit_not_cut(hit, e, llst, ray))
	// 			hit_anything = 1;
	// 	llst = llst->next;
	// }
	return (hit_anything);
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
	color = multiply_color(hit->hit_obj->col, hit->hit_obj->coef.z);
	while (llst)
	{
		s = shadows(e, hit, llst, ray);
		hit->lm = vec_norm(vec_sub(llst->pos, hit->v));
		hit->cost = vec_dot(hit->n, hit->lm);
		color = add_color(multiply_color(specular_diffuse(llst, hit), s), color);
		llst = llst->next;
	}
	if (!(textures_coef(hit->hit_obj, hit, ray)))
		color = multiply_color(color, 0.6);
	return (color);
}

int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray)
{
	int	pixel;

	hit->nr = 1;
	hit->nt = 1;
	hit->hit_inter = inter_position(ray, hit->t);
	pixel = phong_lighting(e, ray, hit);
	if (hit->hit_obj->tr > 0 && hit->nt > 0)
		pixel = transparency(e, pixel, ray, hit);
	if (hit->hit_obj->r > 0.01 && hit->nr > 0)
		pixel = reflection(e, pixel, ray, hit);
	return (pixel);
}

// t_vclist	*compute_lights(t_env *e, t_hit_rec *hit_rec, t_ray ray)
// {
// 	t_vclist	*b_lights;
//
// }

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
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				// if (hit_rec->type == 1)
				// 	vclist_add()
				// else
					px_color = compute_point(e, &hit_rec, ray);
					draw_point(e, e->y, e->z, px_color);
			}
		}
	}
	// blinding_lights(e);
	// stereoscopic(e);
	return (NULL);
}
