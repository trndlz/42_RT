/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 13:45:01 by jostraye         ###   ########.fr       */
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

int		compute_point(t_env *e, t_hit_rec *hit, t_ray ray, int a)
{
	int	pixel;

	hit->hit_inter = inter_position(ray, hit->t);
	pixel = phong_lighting(e, ray, hit);
	if (hit->hit_obj->descartes.x > 0.01 && e->nr > 0 && a != 0)
		pixel = reflection(e, pixel, ray, hit);
	if (hit->hit_obj->descartes.y > 0.01 && e->nt > 0 && a != 1)
		pixel = transparency(e, pixel, ray, hit);
	pixel = apply_filter(e, pixel);
	return (pixel);
}

void	*scene_plot(void *arg)
{
	t_env		*e;
	t_ray		ray;
	t_hit_rec	hit_rec;
	int			color;

	e = (t_env *)arg;
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			e->nr = 2;
			e->nt = 10;
			ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
			if (nearest_node(e, ray, &hit_rec))
			{
				color = compute_point(e, &hit_rec, ray, 3);
				draw_point(e, e->y, e->z, color);
			}
			if (e->scene.filter == STEREOSCOPIC)
				stereoscopic(e, color);
		}
	}
	return (NULL);
}
