/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*default_paraboloid(void)
{
	t_obj *parab;

	if (!(parab = malloc(sizeof(t_obj))))
		return (NULL);
	parab->o_type = PARABOLOID;
	parab->pos = (t_vc){0, 0, 0};
	parab->rot = (t_vc){0, 0, -1};
	parab->size = 50;
	parab->col = ft_htoi("0x900C3F");
	parab->texture = NO_TEXTURE;
	parab->txt_size = 200;
	parab->descartes = (t_vc){0, 0, 1.0};
	parab->phong = (t_vc){0.5, 0.5, 0.2};
	parab->cut = NULL;
	parab->perturb = 0;
	return (parab);
}
