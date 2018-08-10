/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 17:10:12 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*default_sphere(void)
{
	t_obj *sphere;

	if (!(sphere = malloc(sizeof(t_obj))))
		return (NULL);
	sphere->o_type = SPHERE;
	sphere->pos = (t_vc){0, 0, 0};
	sphere->rot = (t_vc){0, 0, 0};
	sphere->size = 100;
	sphere->col = ft_htoi("0xFF5733");
	sphere->texture = NO_TEXTURE;
	sphere->txt_size = 12;
	sphere->descartes = (t_vc){0, 0, 1.0};
	sphere->phong = (t_vc){0.5, 0.5, 0.2};
	sphere->cut = NULL;
	sphere->perturb = 0;
	return (sphere);
}

t_obj		*default_cone(void)
{
	t_obj *cone;

	if (!(cone = malloc(sizeof(t_obj))))
		return (NULL);
	cone->o_type = CONE;
	cone->pos = (t_vc){0, 0, 0};
	cone->rot = (t_vc){0, 0, 1};
	cone->size = 15;
	cone->col = ft_htoi("0xFFC300");
	cone->texture = NO_TEXTURE;
	cone->txt_size = 100;
	cone->descartes = (t_vc){0, 0, 1.0};
	cone->phong = (t_vc){0.5, 0.5, 0.2};
	cone->cut = NULL;
	cone->perturb = 0;
	return (cone);
}

t_obj		*default_cylinder(void)
{
	t_obj *cylinder;

	if (!(cylinder = malloc(sizeof(t_obj))))
		return (NULL);
	cylinder->o_type = CYLINDER;
	cylinder->pos = (t_vc){0, 0, 0};
	cylinder->rot = (t_vc){0, 0, 1};
	cylinder->size = 150;
	cylinder->col = ft_htoi("0x900C3F");
	cylinder->texture = NO_TEXTURE;
	cylinder->txt_size = 200;
	cylinder->descartes = (t_vc){0, 0, 1.0};
	cylinder->phong = (t_vc){0.5, 0.5, 0.2};
	cylinder->cut = NULL;
	cylinder->perturb = 0;
	return (cylinder);
}

t_obj		*default_plane(void)
{
	t_obj *plane;

	if (!(plane = malloc(sizeof(t_obj))))
		return (NULL);
	plane->o_type = PLANE;
	plane->pos = (t_vc){10000, 0, 0};
	plane->rot = (t_vc){-1, 0, 0};
	plane->col = ft_htoi("0xDAF7A6");
	plane->texture = NO_TEXTURE;
	plane->txt_size = 320;
	plane->descartes = (t_vc){0, 0, 1.0};
	plane->phong = (t_vc){0.5, 0.5, 0.2};
	plane->cut = NULL;
	plane->perturb = 0;
	return (plane);
}

t_obj		*default_cutter(t_obj *obj)
{
	t_obj *cut;

	if (!(cut = malloc(sizeof(t_obj))))
		return (NULL);
	cut->o_type = PLANE;
	cut->pos = (t_vc){0, 0, 0};
	cut->rot = (t_vc){0, 0, 1};
	cut->col = obj->col;
	cut->texture = NO_TEXTURE;
	cut->txt_size = 12;
	cut->size = 100;
	cut->descartes = obj->descartes;
	cut->phong = obj->phong;
	cut->cut = NULL;
	cut->perturb = 0;
	return (cut);
}
