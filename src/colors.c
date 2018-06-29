/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/29 15:18:55 by tmervin          ###   ########.fr       */
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
	b = color_limits(hex % 0X100);
	g = color_limits((hex / 0X100) % 0X100);
	r = color_limits((hex / (0X100 * 0X100)) % 0X100);
	hex = (int)(mult * b) + (int)(mult * g) * 0X100 +
	(int)(mult * r) * 0X100 * 0X100;
	return (hex);
}

int			add_color(int hex1, int hex2)
{
	int r;
	int g;
	int b;

	r = color_limits((hex1 / (0X100 * 0X100)) % 0X100
		+ (hex2 / (0X100 * 0X100)) % 0X100);
	g = color_limits((hex1 / 0X100) % 0X100 + (hex2 / 0X100) % 0X100);
	b = color_limits(hex1 % 0X100 + hex2 % 0X100);
	return (((int)(r & 0xff) << 16) + ((int)(g & 0xff) << 8) + (int)(b & 0xff));
}

int		get_texture_sphere(t_env *e, t_obj *obj)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom), obj->pos), (1/obj->size)));
	sph_pos = rot_all_axis(sph_pos, obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	return (obj->texture_tab[(int)(v * obj->texture_size[1])][(int)(u * obj->texture_size[0])]);
}

int		get_lines_sphere(t_env *e, t_obj *obj)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom), obj->pos), (1/obj->size)));
	sph_pos = rot_all_axis(sph_pos, obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if ((int)(12 * v) % 2)
		return (obj->col);
	else
		return (multiply_color(obj->col, 0.2));
}

int		get_columns_sphere(t_env *e, t_obj *obj)
{
	double	u;
	double	v;
	t_vc	sph_pos;

	sph_pos = vec_norm(vec_mult(vec_sub(vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom), obj->pos), (1/obj->size)));
	sph_pos = rot_all_axis(sph_pos, obj->rot);
	u = 0.5 + atan2(sph_pos.z, sph_pos.y) / (2 * M_PI);
	v = 0.5 - asin(sph_pos.x) / M_PI;
	if ((int)(90 * u) % 2)
		return (obj->col);
	else
		return (multiply_color(obj->col, 0.2));
}

int		get_checkers_plane(t_env *e, t_obj *obj)
{
	t_vc	plane_pos;
	t_vc	bv1;
	t_vc	bv2;

	bv1 = vec_norm(init_vc(1, 0, obj->pos.y / obj->pos.z));
	bv2 = vec_norm(init_vc(0, 1, obj->pos.y / obj->pos.z));
	plane_pos = vec_sub(vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom), obj->pos);
	if (((int)(plane_pos.x) + (int)(plane_pos.y)) % 2)
		return (obj->col);
	else
		return (0x000000);
}

int			specular_diffuse(int color, t_obj *light, t_obj *obj, t_env *e)
{
	int		color_diff;
	int		color_spec;
	double	dot_spec;
	double	dot_diff;

	e->rm = vec_norm(vec_sub(vec_mult(e->n, 2 * e->cost), e->lm));
	dot_spec = ratio_limits(pow(vec_dot(e->rm, vec_mult(e->v2, -1.0)),
		ALPHA_SPEC));
	dot_diff = ratio_limits(e->cost);
	color_spec = multiply_color(light->col, dot_spec * obj->coef.x);
	if (obj->type == 3 && SPHERE_TEXTURE == 1)
		color_diff = multiply_color(get_texture_sphere(e, obj), dot_diff * obj->coef.y);
	else if (obj->type == 6 && PLANE_CHECKERS == 1)
		color_diff = multiply_color(get_checkers_plane(e, obj), dot_diff * obj->coef.y);
	else
		color_diff = multiply_color(obj->col, dot_diff * obj->coef.y);
	color_spec = add_color(color_spec, color_diff);
	color_spec = add_color(color_spec, color);
	return (color_spec);
}
