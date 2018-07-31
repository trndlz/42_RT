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

enum texture	texture_converter(char *str, enum obj_type obj)
{
	if (!ft_strcmp(str, "LINES")
		&& (obj == CYLINDER || obj == CONE || obj == SPHERE))
		return (LINES);
	else if (!ft_strcmp(str, "COLUMNS") && obj == SPHERE)
		return (COLUMNS);
	else if (!ft_strcmp(str, "CHECKERBOARD")
		&& (obj == SPHERE || obj == PLANE))
		return (CHECKERBOARD);
	else if (!ft_strcmp(str, "EARTH") && obj == SPHERE)
		return (EARTH);
	else if (!ft_strcmp(str, "NEARTH") && obj == SPHERE)
		return (NEARTH);
	else
		return (NO_TEXTURE);
}

enum filter		filter_converter(char *str)
{
	if (!ft_strcmp(str, "CARTOON"))
		return (CARTOON);
	else if (!ft_strcmp(str, "SEPIA"))
		return (SEPIA);
	else if (!ft_strcmp(str, "RED"))
		return (RED);
	else if (!ft_strcmp(str, "GREEN"))
		return (GREEN);
	else if (!ft_strcmp(str, "BLUE"))
		return (BLUE);
	else if (!ft_strcmp(str, "CYAN"))
		return (CYAN);
	else if (!ft_strcmp(str, "STEREOSCOPIC"))
		return (STEREOSCOPIC);
	else
		return (NO_FILTER);
}

char			*parse_texture(char *file, enum texture *texture, enum obj_type obj)
{
	int		check;
	char	str[30];

	if ((check = sscanf(file, "%*s %15s\n", str) != 1))
		return (parser_error("Invalid texture values\n", file));
	*texture = texture_converter(str, obj);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_filter(char *file, enum filter *filter)
{
	int		check;
	char	str[30];

	if ((check = sscanf(file, "%*s %15s\n", str) != 1))
		return (parser_error("Invalid filter values !\n", file));
	*filter = filter_converter(str);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}
