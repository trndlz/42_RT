/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:06:54 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/12 15:56:23 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

// All filters fo the RT projects will be set here

// void	stereoscopic(t_env *e)
// {
// 	int *colorcopy;
// 	int i;
// 	t_obj	*tmp;
//
// 	i = ((e->thread_int) * WINZ / TH_NB) * WINY - 1;
// 	colorcopy = (int *)malloc(sizeof(int) * WINY * WINZ);
// 	global_filter(e, 2);
// 	e->z = (e->thread_int) * WINZ / TH_NB - 1;
// 	e->eye_lookfrom.y -= 60;
// 	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
// 	{
// 		e->y = -1;
// 		while (++(e->y) < WINY)
// 		{
// 			colorcopy[e->z * WINY + e->y] = e->imgstr[e->z * WINY + e->y];
// 			create_ray(e);
// 			tmp = nearest_node(e);
// 			if (tmp)
// 			{
// 				e->offset = vec_sub(e->eye_lookfrom, tmp->pos);
// 				compute_scene_vectors(e, tmp);
// 			}
// 		}
// 	}
// 	global_filter(e, 3);
// 	while (++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
// 		e->imgstr[i] = add_color(e->imgstr[i], colorcopy[i]);
// }

int	sepia_filter(t_env *e, int i)
{
	t_vc rgb;
	t_vc sepiargb;
	int color;

	color = 0;
	rgb = hextorgb(e->imgstr[i]);
	sepiargb.x = ((double)(rgb.x * 393) + (rgb.y * 769) + (rgb.z * 189)) / 1000;
	sepiargb.y = ((double)(rgb.x * 349) + (rgb.y * 686) + (rgb.z * 168)) /1000;
	sepiargb.z = ((double)(rgb.x * 272) + (rgb.y * 534) + (rgb.z * 131)) /1000;
	color = color_limits(sepiargb.x) * 256 * 256 +
	color_limits(sepiargb.y) * 256 + color_limits(sepiargb.z);
	return (color);
}

void global_filter(t_env *e, int filter)
{
	int i;

	i = ((e->thread_int) * WINZ / TH_NB) * WINY - 1;
	if (filter == -1 || !filter)
		exit (0);
	if (filter == 0)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = e->imgstr[i] % 0X100;
	if (filter == 1)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = ((e->imgstr[i] / 0X100) % 0X100) * 0X100;
	if (filter == 2)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = ((e->imgstr[i] / (0X100 * 0X100)) % 0X100) * (0X100 * 0X100);
	if (filter == 3)
	while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
		e->imgstr[i] = e->imgstr[i] % 0X100 + ((e->imgstr[i] / 0X100) % 0X100) * 0X100;
	if (filter == 4)
		while(++i < (((e->thread_int + 1) * WINZ) / TH_NB) * WINY)
			e->imgstr[i] = sepia_filter(e, i);
}
