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

char		*objects_items(t_obj *sphere, char *file, enum obj_type obj)
{
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(sphere->pos));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(sphere->rot));
		else if (ft_strncmp("[size] ", file, 7) == 0)
			file = parse_double(file, &(sphere->size));
		else if (ft_strncmp("[color] ", file, 8) == 0)
			file = parse_color(file, &(sphere->col));
		else if (ft_strncmp("[texture] ", file, 10) == 0)
			file = parse_texture(file, &(sphere->texture), obj);
		else if (ft_strncmp("[R/T/Rf] ", file, 9) == 0)
			file = parse_descartes(file, &(sphere->descartes));
		else if (ft_strncmp("[Spec/Diff/Amb] ", file, 16) == 0)
			file = parse_phong(file, &(sphere->coef));
		else if (ft_strncmp("[perturbation] ", file, 15) == 0)
			file = parse_int(file, &(sphere->perturb));
		else if (ft_strncmp("<cutter>\n", file, 9) == 0)
			file = parse_cutter(sphere, file + 9);
		else
			break ;
	}
	return (file);
}

char		*parse_sphere(t_env *e, char *file)
{
	t_obj *sphere;

	sphere = default_sphere();
	file = objects_items(sphere, file, SPHERE);
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
