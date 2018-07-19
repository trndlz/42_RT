/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:26:30 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/19 18:29:07 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
# define PALETTE_SIZE 5
// void	aa_create_ray(t_env *e, double offy, double offz)
// {
// 	e->ray.x = (double)(FOV);
// 	e->ray.y = (double)(WINY / 2 - e->y) - offy;
// 	e->ray.z = (double)(WINZ / 2 - e->z) - offz;
// 	e->ray = rot_all_axis(e->ray, e->eye_rot);
// }
//
// void		aa_draw_point(t_env *e, unsigned int color)
// {
// 	int i;
// 	double aa_color;
// 	i = (e->y + ((e->z * e->s_l) / 4));
// 	aa_color = multiply_color(color, 0.25);
// 	if (i >= 0 && i < (WINY * WINZ))
// 		e->imgstr[i] = add_color(aa_color, e->imgstr[i]);
// }
//
// void	aa_compute_scene_vectors(t_env *e, t_obj *tmp)
// {
// 	t_obj	*llst;
// 	int		color;
// 	int		is_lit;
//
// 	llst = e->light_link;
// 	color = multiply_color(tmp->col, tmp->coef.z);
// 	aa_draw_point(e, color);
// 	while (llst)
// 	{
// 		normal_vectors(e, tmp);
// 		e->v2 = vec_add(vec_add(vec_mult(e->ray, e->t), e->offset), tmp->pos);
// 		e->lm = vec_norm(vec_sub(llst->pos, e->v2));
// 		e->cost = vec_dot(e->n, e->lm);
// 		is_lit = shadows(e, tmp, e->obj_link, llst);
// 		if (is_lit)
// 		{
// 			color = specular_diffuse(color, llst, tmp, e);
// 			aa_draw_point(e, color);
// 		}
// 		else
// 			aa_draw_point(e, 0X000000);
//
// 		llst = llst->next;
// 	}
// }

// void	antialias(t_env *e)
// {
// 	t_obj	*tmp;
// 	double offy;
// 	double offz;
// 	int i;
//
// 	e->z = ((e->thread_int) * WINZ / TH_NB - 1);
// 	while (++(e->z) < (((e->thread_int + 1) * WINZ) / TH_NB))
// 	{
// 		e->y = -1;
// 		while (++(e->y) < WINY)
// 		{
// 			i = (e->y + ((e->z * e->s_l) / 4));
// 			e->imgstr[i] = 0;
// 			offy = 0;
// 			offz = 0;
// 			while (offy + offz < 1.5)
// 			{
// 				aa_create_ray(e, offy, offz);
// 				tmp = nearest_node(e);
// 				if (tmp)
// 				{
// 					e->offset = vec_sub(e->eye_lookfrom, tmp->pos);
// 					aa_compute_scene_vectors(e, tmp);
// 				}
// 				if (e->y == 500 && e->z == 500)
// 				printf("y %fz %f\n",offy, offz);
// 				if (offy == 0 && offz == 0)
// 					offy = 0.5;
// 				else if (offy == 0.5 && offz == 0)
// 				{
// 					offz = 0.5;
// 					offy = 0;
// 				}
// 				else
// 					offy += 0.5;
// 			}
// 		}
// 	}
// }

int		clr_abs_dif(int col1, int col2)
{
	t_vc rgb1;
	t_vc rgb2;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb1 = vec_sub(rgb1, rgb2);
	ret = fabs(rgb1.x) + fabs(rgb1.y) + fabs(rgb1.z);
	return (ret);
}

int		av_col_four(int col1, int col2, int col3, int col4)
{
	t_vc rgb;
	t_vc rgb1;
	t_vc rgb2;
	t_vc rgb3;
	t_vc rgb4;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb3 = hextorgb(col3);
	rgb4 = hextorgb(col4);
	rgb.x = color_limits((rgb1.x + rgb2.x + rgb3.x + rgb4.x) / 4);
	rgb.y = color_limits((rgb1.y + rgb2.y + rgb3.y + rgb4.y) / 4);
	rgb.z = color_limits((rgb1.z + rgb2.z + rgb3.z + rgb4.z) / 4);
	ret = rgb.x * 0x100 * 0x100 + rgb.y * 0x100 + rgb.z;
	return (ret);
}

int		av_col_two(int col1, int col2)
{
	t_vc rgb;
	t_vc rgb1;
	t_vc rgb2;
	int ret;

	rgb1 = hextorgb(col1);
	rgb2 = hextorgb(col2);
	rgb.x = color_limits((rgb1.x + rgb2.x) / 2);
	rgb.y = color_limits((rgb1.y + rgb2.y) / 2);
	rgb.z = color_limits((rgb1.z + rgb2.z) / 2);
	ret = rgb.x * 0x100 * 0x100 + rgb.y * 0x100 + rgb.z;
	return (ret);
}

char	aa_condition(int *imgstr, int y, int z, int sensib)
{
	if (clr_abs_dif(imgstr[z * WINY + y + 1],
		imgstr[z * WINY + y + WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y + 1],
		imgstr[z * WINY + y - WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y - 1],
		imgstr[z * WINY + y + WINY]) > sensib
	|| clr_abs_dif(imgstr[z * WINY + y - 1],
		imgstr[z * WINY + y - WINY]) > sensib)
		return (1);
	else
		return (0);
}

char	cart_condition(int *imgstr, int y, int z, int sensib)
{
	if (clr_abs_dif(imgstr[z * WINY + y], imgstr[z * WINY + y + 1])
	+ clr_abs_dif(imgstr[z * WINY + y], imgstr[z * WINY + y - 1])
	+ clr_abs_dif(imgstr[z * WINY + y], imgstr[z * WINY + y + WINY])
	+ clr_abs_dif(imgstr[z * WINY + y], imgstr[z * WINY + y - WINY]) > sensib)
		return (1);
	else
		return (0);
}

void	antialias(t_env *e)
{
	int *colorcopy;

	e->z = 0;
	colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ);
	colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
	while (++(e->z) < WINZ - 1)
	{
		colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
		e->y = 0;
		while (++(e->y) < WINY - 1)
		{


			colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
			if (aa_condition(e->imgstr, e->y, e->z, AA_S))
				colorcopy[e->z * WINY + e->y] = av_col_two(av_col_four(e->imgstr[e->z * WINY + e->y + 1], e->imgstr[e->z * WINY + e->y + WINY],
				e->imgstr[e->z * WINY + e->y - WINY], e->imgstr[e->z * WINY + e->y - 1 ]),e->imgstr[e->z * WINY + e->y]);
					if (e->y == 639 && e->z == 500)
						printf("%#08x\n",colorcopy[e->z * WINY + e->y]);
		}
	}
	e->z = - 1;
	while (++e->z < WINZ)
	{
		e->y = -1;
		while (++(e->y) < WINY)
			e->imgstr[e->z * WINY + e->y] = colorcopy[e->z * WINY + e->y];
	}
}
// char	*flatten_color(t_env *e, int * colorcopy, char *cartooned, int sensib)
// {
// 	int i = e->y - 2;
// 	while (++i < e->y + 2)
// 	{
// 		int j = e->z - 2;
// 		while(++j < e->z + 2)
// 		{
// 			if (clr_abs_dif(e->imgstr[e->z * WINY + e->y], e->imgstr[j * WINY + i]) < sensib)
// 			{
// 				colorcopy[j * WINY + i] = e->imgstr[e->z * WINY + e->y];
// 				cartooned[j * WINY + i] = 1;
// 			}
// 			else if (clr_abs_dif(e->imgstr[e->z * WINY + e->y], e->imgstr[j * WINY + i]) > sensib && clr_abs_dif(e->imgstr[e->z * WINY + e->y], 0x000000) > 250)
// 				colorcopy[j * WINY + i] = 0xffffff;
// 			else
// 				colorcopy[j * WINY + i] = 0x00000;
// 		}
// 	}
// 	return (cartooned);
// }

// void	cartooning(t_env *e)
// {
// 	int *colorcopy;
// 	int *palette;
// 	e->z = -1;
// 	colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ);
// 	palette = (int *)malloc(sizeof(int) * PALETTE_SIZE);
// 	palette[0] = e->imgstr[0];
// 	palette[1] = -1;
// 	while (++(e->z) < WINZ)
// 	{
// 		e->y = -1;
// 		while (++(e->y) < WINY)
// 			//pour chaque px comparer avec l'ensemble de la palette
// 			//si tres differents de toutes les couleurs - > nouvelle coueleur
// 	}
// 	e->z = 0;
//
// 	while (++(e->z) < WINZ - 1)
// 	{
// 		e->y = 0;
// 		while (++(e->y) < WINY - 1)
// 		{
//
// 			cartooned = flatten_color(e, colorcopy, cartooned, 10);
// 			// if (aa_condition(e->imgstr, e->y + 1, e->z, 5))
// 			// 	colorcopy[e->z * WINY + e->y] = 0x000000;
// 			// else
// 			// 	colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
// 		}
// 	}
// 	e->z = - 1;
// 	while (++e->z < WINZ)
// 	{
// 		e->y = -1;
// 		while (++(e->y) < WINY)
// 			e->imgstr[e->z * WINY + e->y] = colorcopy[e->z * WINY + e->y];
// 	}
// }
