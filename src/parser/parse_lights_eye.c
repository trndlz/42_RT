/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_eye.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Eye par défaut à créer autre part !
*/

char		*parse_eye(t_env *e, char *file)
{
	e->eye_lookfrom = (t_vc){-1000, 0, 0};
	e->eye_rot = (t_vc){0, 0, 0};
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

char		*parse_light(t_env *e, char *file)
{
	t_obj *light;

	if (!(light = malloc(sizeof(t_obj))))
		return (NULL);
	light->pos = (t_vc){-1000, 0, 0};
	light->rot = (t_vc){0, 0, 0};
	light->col = ft_htoi("0xFFFFFF");
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
	obj_add(&e->light_link, light);
	return (file);
}
