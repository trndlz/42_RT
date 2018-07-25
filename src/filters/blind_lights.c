/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blind_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:54:34 by jostraye          #+#    #+#             */
/*   Updated: 2018/07/24 13:12:20 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rtv1.h"
//
// void		vclist_add(t_vclist **beg, t_vclist *n)
// {
// 	if (!beg || !n)
// 		return ;
// 	else
// 	{
// 		n->next = *beg;
// 		*beg = n;
// 	}
// }
//
// double		blinding_condition(t_env *e, t_vc light)
// {
// 	double coef;
// 	if (light.x == 0 || e->y - light.y == 0)
// 		return (1);
// 	else
// 		coef = 1 / (fabs(e->y - light.y) * sqrt(fabs(e->z - light.z))) * WINY * 100 / light.x +
// 		1 / (fabs(e->z - light.z) * sqrt(fabs(e->y - light.y))) * WINZ * 100 / light.x;
// 	if (coef > 1)
// 		coef = 1;
// 	if (coef < 0)
// 		coef = 0;
// 	return (coef);
// }
//
// void	blinding_lights(t_env *e, t_hit_rec *hit)
// {
// 	t_vc	light;
// 	light.x = hit->t;
// 	light.y = e->y;
// 	light.z = e->z;
// 	double		bld_coef;
// 	e->z = (e->thread_int) * WINZ / TH_NB - 1;
// 	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
// 	{
// 		e->y = -1;
// 		while (++(e->y) < WINY)
// 		{
// 			if((bld_coef = blinding_condition(e, light)))
// 			{
// 				e->imgstr[e->z * WINY + e->y] = mix_colors(0xFFFFFF, e->imgstr[e->z * WINY + e->y], bld_coef);
// 			}
// 		}
// 	}
// }
