/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:47:23 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/13 17:44:15 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*new_sphere(int k)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	k+=0;
	new->type = 1;
	new->pos = init_vc(1000, 0, 100);
	new->size = 200;
	new->color[0] = 224;
	new->color[1] = 17;
	new->color[2] = 95;
	new->ks = 0.5;
	new->ka = 0.5;
	new->kd = 0.5;
	new->next = NULL;
	return (new);
}

t_obj		*new_cone(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 3;
	new->rot = init_vc(0, 0, 0);
	new->pos = init_vc(3000, 200, 1000);
	new->size = 1;
	new->color[0] = 255;
	new->color[1] = 204;
	new->color[2] = 51;
	new->ks = 0.5;
	new->ka = 0.5;
	new->kd = 0.5;
	new->next = NULL;
	return (new);
}

t_obj		*new_cylinder(int k)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 2;
	new->rot = init_vc(0, 0, 0);
	new->pos = init_vc(1000, k * 100, 0);
	new->size = 20;
	new->color[0] = 62;
	new->color[1] = 180;
	new->color[2] = 137;
	new->ks = 0.2;
	new->ka = 0.2;
	new->kd = 0.2;
	new->next = NULL;
	return (new);
}

t_obj		*new_light(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 5;
	new->pos = init_vc(0, 0, 0);
	new->color[0] = 255;
	new->color[1] = 255;
	new->color[2] = 255;
	new->next = NULL;
	return (new);
}

t_obj		*new_plane(int a, int b, int c)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 4;
	new->rot = init_vc(a, b, c);
	new->pos = init_vc(a, b, c);
	new->color[0] = 190;
	new->color[1] = 190;
	new->color[2] = 190;
	new->ks = 0;
	new->ka = 0.8;
	new->kd = 1;
	new->next = NULL;
	return (new);
}
