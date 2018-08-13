/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:06:54 by jostraye          #+#    #+#             */
/*   Updated: 2018/08/13 09:38:50 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	stereoscopic(t_env *e, int color)
{
	t_hit_rec	hit_rec;
	t_ray		ray;
	int			px_color;

	ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
	ray.origin.y -= 60;
	if (nearest_node(e, ray, &hit_rec))
	{
		px_color = compute_point(e, &hit_rec, ray, 3);
		px_color = px_color % 0x100 + ((px_color / 0x100) % 0x100) * 0x100;
		color = ((color / (0x100 * 0x100)) % 0x100) * (0x100 * 0x100);
		draw_point(e, e->y, e->z, add_color(px_color, color));
	}
}

int		sepia(int color)
{
	t_vc rgb;
	t_vc sepiargb;

	rgb = hextorgb(color);
	sepiargb.x = ((double)(rgb.x * 393) + (rgb.y * 769) + (rgb.z * 189)) / 1000;
	sepiargb.y = ((double)(rgb.x * 349) + (rgb.y * 686) + (rgb.z * 168)) / 1000;
	sepiargb.z = ((double)(rgb.x * 272) + (rgb.y * 534) + (rgb.z * 131)) / 1000;
	return (color_limits(sepiargb.x) * 256 * 256 +
	color_limits(sepiargb.y) * 256 + color_limits(sepiargb.z));
}

int		apply_filter(t_env *e, int color)
{
	if (e->scene.filter == NO_FILTER)
		return (color);
	else if (e->scene.filter == BLUE)
		return (color % 0x100);
	else if (e->scene.filter == GREEN)
		return (((color / 0x100) % 0x100) * 0x100);
	else if (e->scene.filter == RED)
		return (((color / (0x100 * 0x100)) % 0x100) * (0x100 * 0x100));
	else if (e->scene.filter == CYAN)
		return (color % 0x100 + ((color / 0x100) % 0x100) * 0x100);
	else if (e->scene.filter == SEPIA)
		return (sepia(color));
	else
		return (color);
}
