/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_other_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 16:52:47 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*parse_eye(t_env *e, char *file)
{
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(e->eye_lookfrom));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(e->eye_rot));
		else
			break ;
	}
	return (file);
}

void		parallel_lights(t_obj *light)
{
	if (light->rot.x == 0 && light->rot.y == 0 && light->rot.z == 0)
		return ;
	else
		light->pos = vec_mult(light->rot, SUN_DISTANCE);
}

char		*parse_light(t_env *e, char *file)
{
	t_obj *light;

	if (!(light = default_light()))
	{
		ft_putstr_fd("Malloc <light> object failed !\n", 2);
		return (file);
	}
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(light->pos));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(light->rot));
		else if (ft_strncmp("[color] ", file, 8) == 0)
			file = parse_color(file, &(light->col));
		else
			break ;
	}
	parallel_lights(light);
	obj_add(&e->light_link, light);
	return (file);
}

char		*parse_cutter(t_obj *obj, char *file)
{
	t_obj *cutter;

	if (!(cutter = default_cutter()))
	{
		ft_putstr_fd("Malloc <cutter> object failed !\n", 2);
		return (file);
	}
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(cutter->pos));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(cutter->rot));
		else if (ft_strncmp("[color] ", file, 8) == 0)
			file = parse_color(file, &(cutter->col));
		else if (ft_strncmp("[R/T/Rf] ", file, 9) == 0)
			file = parse_descartes(file, &(cutter->descartes));
		else if (ft_strncmp("[Spec/Diff/Amb] ", file, 16) == 0)
			file = parse_phong(file, &(cutter->phong));
		else
			break ;
	}
	obj->cut = cutter;
	return (file);
}
