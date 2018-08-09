/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 16:47:34 by jostraye         ###   ########.fr       */
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

t_obj		*default_light(void)
{
	t_obj *light;

	if (!(light = malloc(sizeof(t_obj))))
		return (NULL);
	light->o_type = LIGHT;
	light->pos = (t_vc){-1000, 0, 0};
	light->rot = (t_vc){0, 0, 0};
	light->col = ft_htoi("0xFFFFFF");
	return (light);
}

t_obj		*default_disc(void)
{
	t_obj *disc;

	if (!(disc = malloc(sizeof(t_obj))))
		return (NULL);
	disc->o_type = DISC;
	disc->pos = (t_vc){100, 100, 100};
	disc->rot = (t_vc){-1, 1, 0};
	disc->col = ft_htoi("0xDAF7A6");
	disc->texture = NO_TEXTURE;
	disc->txt_size = 320;
	disc->descartes = (t_vc){0, 0, 1.0};
	disc->phong = (t_vc){0.5, 0.5, 0.2};
	disc->cut = NULL;
	disc->perturb = 0;
	return (disc);
}
