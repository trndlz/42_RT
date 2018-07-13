/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/13 15:09:58 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ratio_limits(double i)
{
	if (i < 0.00001)
		return (0);
	if (i > 1.0)
		return (1.0);
	else
		return (i);
}

int			color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

int			multiply_color(int hex, double mult)
{
	int r;
	int g;
	int b;

	if (mult < 0)
		mult = 0;
	b = color_limits(hex % 0x100);
	g = color_limits((hex / 0x100) % 0x100);
	r = color_limits((hex / (0x100 * 0x100)) % 0x100);
	hex = (int)(mult * b) + (int)(mult * g) * 0x100 +
	(int)(mult * r) * 0x100 * 0x100;
	return (hex);
}

int			add_color(int hex1, int hex2)
{
	int r;
	int g;
	int b;

	r = color_limits((hex1 / (0x100 * 0x100)) % 0x100
		+ (hex2 / (0x100 * 0x100)) % 0x100);
	g = color_limits((hex1 / 0x100) % 0x100 + (hex2 / 0x100) % 0x100);
	b = color_limits(hex1 % 0x100 + hex2 % 0x100);
	return (((int)(r & 0xff) << 16) + ((int)(g & 0xff) << 8) + (int)(b & 0xff));
}

int		get_lines_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(ray.direction, hit->t), ray.origin), hit->hit_obj->pos), (1/hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if ((int)(12 * v) % 2)
		return (hit->hit_obj->col);
	else
		return (multiply_color(hit->hit_obj->col, 0.6));
}

int		get_columns_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(ray.direction, hit->t), ray.origin), hit->hit_obj->pos), (1/hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if ((int)(90 * u) % 2)
		return (hit->hit_obj->col);
	else
		return (multiply_color(hit->hit_obj->col, 0.6));
}

int		get_texture_sphere(t_hit_rec *hit, t_ray ray)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(ray.direction, hit->t), ray.origin), hit->hit_obj->pos), (1/hit->hit_obj->size)));
	sph_pos = rot_all_axis(sph_pos, hit->hit_obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	return (hit->hit_obj->texture_tab[(int)(v * hit->hit_obj->texture_size[1])][(int)(u * hit->hit_obj->texture_size[0])]);
}

int		checkerboard_plane(t_hit_rec *hit, t_ray ray)
{
	t_vc	xy_pos;
	double	teta;
	int		mod;

	xy_pos = vec_sub(vec_add(vec_mult(ray.direction, hit->t), ray.origin), hit->hit_obj->pos);
	teta = acos(vec_dot(hit->hit_obj->rot, init_vc(0, 0, 1)));
	xy_pos = rot_x(xy_pos, (int)(teta * 180 / M_PI));
	xy_pos = rot_y(xy_pos, (int)(teta * 180 / M_PI));
	mod = (xy_pos.x * xy_pos.y > 0) ? 1 : 0;
	if (abs((int)xy_pos.x / 350 - (int)xy_pos.y / 350) % 2 == mod)
	 	return (hit->hit_obj->col);
	else
		return (multiply_color(hit->hit_obj->col, 0.6));
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
	if (obj->type == 3 && SPHERE_TEXTURE == 1)
		color_diff = multiply_color(get_texture_sphere(hit, ray), dot_diff * obj->coef.y);
	else if (obj->type == 6 && PLANE_CHECKERS == 1)
		color_diff = multiply_color(checkerboard_plane(hit, ray), dot_diff * obj->coef.y);
	else
		color_diff = multiply_color(obj->col, dot_diff * obj->coef.y);
	color_spec = add_color(color_spec, color_diff);
	color_spec = add_color(color_spec, color);
	return (color_spec);
}
