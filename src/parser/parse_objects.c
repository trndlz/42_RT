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
	if (sphere->texture == PERLIN)
		sphere->file_txt = create_perlin_tex(10, e);
	if (sphere->texture == NEARTH)
	{
		load_texture_to_obj(e, sphere);
		load_tex_height_to_obj(e, sphere);
	}
	if (sphere->cut && (sphere->descartes.y > 0 || sphere->cut->descartes.y))
		ft_putstr("Transparent <sphere> objects can't be cut !\n");
	else
		obj_add(&(e->obj_link), sphere);
	return (file);
}

char		*parse_cylinder(t_env *e, char *file)
{
	t_obj *cyl;

	cyl = default_cylinder();
	file = objects_items(cyl, file, CYLINDER);
	if (cyl->cut && (cyl->descartes.y > 0 || cyl->cut->descartes.y))
		ft_putstr("Transparent <cylinder> can't be cut !\n");
	else
		obj_add(&(e->obj_link), cyl);
	return (file);
}

char		*parse_cone(t_env *e, char *file)
{
	t_obj *cone;

	cone = default_cone();
	file = objects_items(cone, file, CONE);
	if (cone->cut && (cone->descartes.y > 0 || cone->cut->descartes.y))
		ft_putstr("Transparent <cone> objects can't be cut !\n");
	else
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

	paraboloid = default_paraboloid();
	file = objects_items(paraboloid, file, PARABOLOID);
	obj_add(&e->obj_link, paraboloid);
	return (file);
}
