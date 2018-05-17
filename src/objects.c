/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:47:23 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 14:47:17 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*new_sphere(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 1;
	new->pos = init_vc(0, 0, 0);
	new->size = 86;
	new->color[0] = 224;
	new->color[1] = 17;
	new->color[2] = 95;
	new->next = NULL;
	return (new);
}

t_obj		*new_cone(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 3;
	new->rot = init_vc(0, 1, 1);
	new->pos = init_vc(0, 0, 0);
	new->size = 50;
	new->color[0] = 255;
	new->color[1] = 204;
	new->color[2] = 51;
	new->next = NULL;
	return (new);
}

t_obj		*new_cylinder(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 2;
	new->rot = init_vc(0, 0, 1);
	new->pos = init_vc(0, 0, 0);
	new->size = 70;
	new->color[0] = 62;
	new->color[1] = 180;
	new->color[2] = 137;
	new->next = NULL;
	return (new);
}

t_obj		*new_plane(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->type = 4;
	new->rot = init_vc(0, -1, 0);
	new->pos = init_vc(0, 300, 0);
	new->color[0] = 125;
	new->color[1] = 125;
	new->color[2] = 125;
	new->next = NULL;
	return (new);
}
