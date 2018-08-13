/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_filters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 14:23:12 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

enum e_texture	texture_converter(char *str, enum e_obj obj)
{
	if (!ft_strcmp(str, "LINES")
		&& (obj == CYLINDER || obj == CONE || obj == SPHERE))
		return (LINES);
	else if (!ft_strcmp(str, "COLUMNS") && obj == SPHERE)
		return (COLUMNS);
	else if (!ft_strcmp(str, "CHECKERBOARD")
		&& (obj == SPHERE || obj == PLANE || obj == DISC))
		return (CHECKERBOARD);
	else if (!ft_strcmp(str, "EARTH") && obj == SPHERE)
		return (EARTH);
	else if (!ft_strcmp(str, "PERLIN") && obj == SPHERE)
		return (PERLIN);
	else if (!ft_strcmp(str, "NEARTH") && obj == SPHERE)
		return (NEARTH);
	else
		return (NO_TEXTURE);
}

enum e_filter	filter_converter(char *str)
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

char			*parse_texture(char *file,
				enum e_texture *texture, unsigned int *size, enum e_obj obj)
{
	int				check;
	unsigned int	n_size;
	char			str[30];

	if ((check = sscanf(file, "%*s %15s %d\n", str, &n_size) != 2))
		return (parser_error("Invalid texture values !\n", file));
	if (n_size > 0)
		*size = n_size;
	*texture = texture_converter(str, obj);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_filter(char *file, enum e_filter *filter)
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
