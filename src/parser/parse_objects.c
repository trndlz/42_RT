/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/07 14:32:37 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*parse_sphere(t_env *e, char *file)
{
	t_obj *sphere;

	if (!(sphere = default_sphere()))
	{
		ft_putstr_fd("Malloc <sphere> object failed !\n", 2);
		return (file);
	}
	file = objects_items(sphere, file, SPHERE);
	if (sphere->texture == EARTH || sphere->texture == NEARTH)
		if (!(load_texture_to_obj(e, sphere)))
			return (file);
	if (sphere->texture == PERLIN)
		sphere->file_txt = create_perlin_tex(sphere->txt_size, e, sphere);
	if (sphere->texture == NEARTH)
		if (!(load_tex_height_to_obj(e, sphere)))
			return (file);
	if (sphere->cut && (sphere->descartes.y > 0 || sphere->cut->descartes.y))
	{
		ft_putstr("Transparent <sphere> objects can't be cut !\n");
		return (file);
	}
	obj_add(&(e->obj_link), sphere);
	return (file);
}

char		*parse_cylinder(t_env *e, char *file)
{
	t_obj *cyl;

	if (!(cyl = default_cylinder()))
	{
		ft_putstr_fd("Malloc <cylinder> object failed !\n", 2);
		return (file);
	}
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

	if (!(cone = default_cone()))
	{
		ft_putstr_fd("Malloc <cone> object failed !\n", 2);
		return (file);
	}
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

	if (!(plane = default_plane()))
	{
		ft_putstr_fd("Malloc <plane> object failed !\n", 2);
		return (file);
	}
	file = objects_items(plane, file, PLANE);
	obj_add(&e->obj_link, plane);
	return (file);
}

char		*parse_paraboloid(t_env *e, char *file)
{
	t_obj *paraboloid;

	if (!(paraboloid = default_paraboloid()))
	{
		ft_putstr_fd("Malloc <paraboloid> object failed !\n", 2);
		return (file);
	}
	file = objects_items(paraboloid, file, PARABOLOID);
	obj_add(&e->obj_link, paraboloid);
	return (file);
}
