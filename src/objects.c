/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:47:23 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/12 19:21:09 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*new_sphere(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 1;
	new->pos = init_vc(-50, 0, 35);
	new->size = 25;
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
	new->rot = init_vc(1, 0, 1);
	new->pos = init_vc(0, 0, 0);
	new->size = 20;
	new->color[0] = 255;
	new->color[1] = 204;
	new->color[2] = 51;
	new->ks = 0.5;
	new->ka = 0.5;
	new->kd = 0.5;
	new->next = NULL;
	return (new);
}

t_obj		*new_cylinder(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 2;
	new->rot = init_vc(0, 1, 0);
	new->pos = init_vc(0, 0, 0);
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
	new->pos = init_vc(-400, 0, 400);
	new->color[0] = 255;
	new->color[1] = 255;
	new->color[2] = 255;
	new->next = NULL;
	return (new);
}

t_obj		*new_plane(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 4;
	new->rot = init_vc(0, -1, 1);
	new->pos = init_vc(0, 0, 0);
	new->color[0] = 190;
	new->color[1] = 190;
	new->color[2] = 190;
	new->ks = 0;
	new->ka = 0.8;
	new->kd = 1;
	new->next = NULL;
	return (new);
}
