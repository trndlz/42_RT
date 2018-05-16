/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:47:23 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/16 16:00:30 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*new_sphere(int x)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
        x += 0;
    new->type = 1;
    new->rot = init_vc(0, 0, 0);
    new->pos = init_vc(0, x * 100, 0);
    new->size = 38;
    new->color = 0xE0115F;
    new->next = NULL;
	return (new);
}

t_obj		*new_cone(int x)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
        x += 0;
    new->type = 3;
    new->rot = init_vc(0, -1, 0);
    new->pos = init_vc(0, 0, 25);
    new->size = 50;
    new->color = 0x8B0000;
    new->next = NULL;
	return (new);
}

t_obj		*new_cylinder(int x)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
    x += 0;
    new->type = 2;
    new->rot = init_vc(0, -1, 1);
    new->pos = init_vc(x * 30, x * 50, 0);
    new->size = 30;
    new->color = 0x3EB489;
    new->next = NULL;
	return (new);
}

t_obj		*new_plane(void)
{
	t_obj		*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
    new->type = 4;
    new->rot = init_vc(0, 0, 1);
    new->pos = init_vc(0, 0, -200);
    new->color = 0xCCCCCC;
    new->next = NULL;
	return (new);
}

void	obj_add(t_obj **beg, t_obj *n)
{
	if (!beg || !n)
		return ;
	else
	{
		n->next = *beg;
		*beg = n;
    }
}
