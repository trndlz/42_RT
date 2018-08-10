/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 10:50:57 by avinas            #+#    #+#             */
/*   Updated: 2018/08/10 15:41:22 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_tex_height_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	int		a;
	int		b;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(inter_position(ray, hit->t),
		hit->hit_obj->pos), (1 / hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.x, sph_pos.z) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.y) / M_PI;
	a = (int)(v * (hit->hit_obj->file_height.size[1] - 1));
	b = (int)(u * (hit->hit_obj->file_height.size[0] - 1));
	a = (a < 0) ? 0 : a;
	b = (b < 0) ? 0 : b;
	return (hit->hit_obj->file_height.tab[a][b]);
}

t_vc	bump_map(t_ray ray, t_hit_rec *hit)
{
	t_vc	modif;
	int		red;
	int		green;
	int		blue;
	int		color;

	color = get_tex_height_sphere(hit, ray);
	red = color % 256;
	green = (color % 65536) / 256;
	blue = color / 65536;
	color = red + green + blue;
	if (color > 0)
	{
		modif.x = (red / 127.5 - 1);
		modif.y = (green / 127.5 - 1);
		modif.z = (blue / 127.5 - 1);
		vec_norm(modif);
		return (vec_add(hit->n, vec_mult(modif, 0.75)));
	}
	return (hit->n);
}
