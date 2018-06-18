/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 15:53:42 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				ratio_limits(double i)
{
	if (i < 0.00001)
		return (0);
	if (i > 1.0)
		return (1.0);
	else
		return (i);
}

int					color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

/*
** ka = ambient ratio
** kd = diffuse ratio
*/

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

	b = color_limits((hex1 % 0X100) + (hex2 % 0X100));
	g = color_limits((hex1 / 0X100) % 0X100 + (hex2 / 0X100) % 0X100);
	r = color_limits((hex1 / (0X100 * 0X100)) % 0X100 + (hex2 / (0X100 * 0X100)) % 0X100);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int			specular_diffuse(int color, t_obj *light, t_env *e)
{
	int		new_color;
	double	dot_spec;
	double	dot_diff;

	dot_spec = ratio_limits(pow(vec_dot(e->rm, e->v), 50));
	dot_diff = ratio_limits(e->cost);
	new_color = multiply_color(light->col, dot_spec * 0.5);
	new_color = add_color(multiply_color(light->col, dot_diff * 0.5), new_color);
	return(add_color(color, new_color));
}


unsigned long		rgb_to_hexa(t_obj *obj, t_env *e)
{
	int r;
	int g;
	int b;
	int x;
	int y;
	int z;
	double dotdiffuse;
	double dotspecular;

	dotdiffuse = ratio_limits(e->cost);
	dotspecular = pow(vec_dot(e->rm, e->v), 50);
	dotspecular = ratio_limits(dotspecular);

	// if (dotspecular > 0.6 && obj->type == 1)
	// 	printf("y %d z %d spec %f\n", e->y, e->z, dotspecular);
	x = (obj->col / (0X100 * 0X100)) % 0X100;
	y = (obj->col / 0X100) % 0X100;
	z = (obj->col % 0X100);
	// printf("r1 %d g1 %d b1 %d\n", x, y, z);
	r = x * dotdiffuse + 0.5 * 255 * dotspecular;
	g = y * dotdiffuse + 0.5 * 255 * dotspecular;
	b = z * dotdiffuse + 0.5 * 255 * dotspecular;
	// printf("r2 %d g2 %d b2 %d\n", r, g, b);
	r = color_limits(r);
	g = color_limits(g);
	b = color_limits(b);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
