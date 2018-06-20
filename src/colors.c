/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 16:19:59 by tmervin          ###   ########.fr       */
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
	b = (hex % 0X100);
	g = (hex / 0X100) % 0X100;
	r = (hex / (0X100 * 0X100)) % 0X100;
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
	color_diff = multiply_color(obj->col, dot_diff * obj->coef.y);
	color_spec = add_color(color_spec, color_diff);
	color_spec = add_color(color_spec, color);
	return (color_spec);
}
