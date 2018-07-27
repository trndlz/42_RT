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

char		*parse_cutter(t_obj *obj, char *file)
{
	t_obj *cutter;

	cutter = default_cutter();
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
