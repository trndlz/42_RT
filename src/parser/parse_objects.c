/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*parse_sphere(t_env *e, char *file)
{
	t_obj *sphere;

	sphere = default_sphere();
	file = objects_items(sphere, file, SPHERE);
	if (sphere->texture == EARTH)
		load_texture_to_obj(e, sphere);
	obj_add(&(e->obj_link), sphere);
	return (file);
}

char		*parse_cylinder(t_env *e, char *file)
{
	t_obj *cylinder;

	cylinder = default_cylinder();
	file = objects_items(cylinder, file, CYLINDER);
	obj_add(&e->obj_link, cylinder);
	return (file);
}

char		*parse_cone(t_env *e, char *file)
{
	t_obj *cone;

	cone = default_cone();
	file = objects_items(cone, file, CONE);
	obj_add(&e->obj_link, cone);
	return (file);
}

char		*parse_plane(t_env *e, char *file)
{
	t_obj *plane;

	plane = default_plane();
	file = objects_items(plane, file, PLANE);
	obj_add(&e->obj_link, plane);
	return (file);
}

char		*parse_paraboloid(t_env *e, char *file)
{
	t_obj *paraboloid;

	paraboloid = default_plane();
	file = objects_items(paraboloid, file, PARABOLOID);
	obj_add(&e->obj_link, paraboloid);
	return (file);
}
