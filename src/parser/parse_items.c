/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*objects_items(t_obj *o, char *file, enum e_obj obj)
{
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(o->pos));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(o->rot));
		else if (ft_strncmp("[size] ", file, 7) == 0)
			file = parse_double(file, &(o->size));
		else if (ft_strncmp("[color] ", file, 8) == 0)
			file = parse_color(file, &(o->col));
		else if (ft_strncmp("[texture] ", file, 10) == 0)
			file = parse_texture(file, &(o->texture), &(o->txt_size), obj);
		else if (ft_strncmp("[R/T/Rf] ", file, 9) == 0)
			file = parse_descartes(file, &(o->descartes));
		else if (ft_strncmp("[Spec/Diff/Amb] ", file, 16) == 0)
			file = parse_phong(file, &(o->phong));
		else if (ft_strncmp("[perturbation] ", file, 15) == 0)
			file = parse_int(file, &(o->perturb));
		else if (ft_strncmp("<cutter>\n", file, 9) == 0)
			file = parse_cutter(o, file + 9);
		else
			break ;
	}
	return (file);
}

char		*parse_descartes(char *file, t_vc *v)
{
	int		check;
	t_vc	descartes;

	if ((check = sscanf(file, "%*s %lf %lf %lf\n",
		&(descartes.x), &(descartes.y), &(descartes.z))) != 3)
		return (parser_error("Invalid values !\n", file));
	if (!(descartes.x >= 0 && descartes.x <= 1))
		return (parser_error("Reflection must be [0;1] !\n", file));
	if (!(descartes.y >= 0 && descartes.y <= 1))
		return (parser_error("Transparency must be [0;1] !\n", file));
	if (!(descartes.z >= 1))
		return (parser_error("Refraction must be > 1 !\n", file));
	*v = descartes;
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char		*parse_phong(char *file, t_vc *v)
{
	int		check;
	t_vc	phong;

	if ((check = sscanf(file, "%*s %lf %lf %lf\n",
		&(phong.x), &(phong.y), &(phong.z))) != 3)
		return (parser_error("Invalid values !\n", file));
	if (phong.x < 0 || phong.y < 0 || phong.z < 0)
		return (parser_error("Values must be [0;1] !\n", file));
	if (phong.x > 1 || phong.y > 1 || phong.z > 1)
		return (parser_error("Values must be [0;1] !\n", file));
	*v = phong;
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}
