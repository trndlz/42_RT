/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:41:47 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:47 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	TEXTURES CHOSER
*/

char		textures_coef(t_obj *obj, t_hit_rec *hit, t_ray ray)
{
	if (obj->o_type == SPHERE && obj->texture == COLUMNS)
		return (get_columns_sphere(hit, ray));
	else if (obj->o_type == SPHERE && obj->texture == LINES)
		return (get_lines_sphere(hit, ray));
	else if (obj->o_type == SPHERE && obj->texture == CHECKERBOARD)
		return (get_checkerboard_sphere(hit, ray));
	else if (obj->o_type == PLANE && obj->texture == CHECKERBOARD)
		return (checkerboard_plane(hit, ray));
	else if (obj->o_type == CYLINDER && obj->texture == LINES)
		return (get_lines_cylinder(hit, ray));
	else if (obj->o_type == DISC && obj->texture == CHECKERBOARD)
		return (checkerboard_plane(hit, ray));
	else if (obj->o_type == CONE && obj->texture == LINES)
		return (get_lines_cone(hit, ray));
	else
		return (0);
}
