/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 14:42:09 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned long		rgb_to_hexa(t_obj *obj, double cost)
{
	int r;
	int g;
	int b;

	r = obj->color[0] * cost;
	g = obj->color[1] * cost;
	b = obj->color[2] * cost;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
