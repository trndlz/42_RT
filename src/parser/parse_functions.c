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

char			*skip_whitespace(char *file)
{
	while (*file == ' ' || *file == '\t')
		file++;
	if (*file == '\n')
		file++;
	return (file);
}

int		ft_htod(char c)
{
	if (ft_isdigit(c))
		return ((int)(c - 48));
	else if ('A' <= 'c' && 'F' >= c)
		return ((int)(c - 55));
	else if ('a' <= c && 'f' >= c)
		return ((int)(c - 87));
	else
		return (-1);
}

int		ft_htoi(char *str)
{
	int i;
	int color;

	color = 0;
	i = 2;
	while (str[0] != '0' && (str[1] != 'x' || str[1] != 'X'))
		return (-1);
	while (str[i])
	{
		if (ft_htod(str[i]) >= 0)
			color = ft_htod(str[i]) + color * 16;
		i++;
	}
	return (color);
}

char			*parse_vc(char *file, t_vc *v)
{
	int		check;

	if ((check = sscanf(file, "%*s %lf %lf %lf\n",
		&(v->x), &(v->y), &(v->z))) != 3)
		return (parser_error("Invalid values !\n", file));
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_descartes(char *file, t_vc *v)
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

char			*parse_phong(char *file, t_vc *v)
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

char			*parse_double(char *file, double *d)
{
	int		check;

	if ((check = sscanf(file, "%*s %lf \n", (d)) != 1))
		return (parser_error("Invalid value !\n", file));
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_int(char *file, int *d)
{
	int		check;

	if ((check = sscanf(file, "%*s %d \n", (d)) != 1))
		return (parser_error("Invalid value !\n", file));
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_color(char *file, int *col)
{
	int		check;
	char	colstr[256];

	if ((check = sscanf(file, "%*s %s\n", colstr) != 1))
		return (parser_error("Invalid color values\n", file));
	*col = ft_htoi(colstr);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

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
	else
		return (NONE);
}

char			*parse_texture(char *file, enum texture *texture,
				enum obj_type obj)
{
	int		check;
	char	str[30];

	if ((check = sscanf(file, "%*s %s\n", str) != 1))
		return (parser_error("Invalid values\n", file));
	*texture = texture_converter(str, obj);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

void			print_vc(t_vc v)
{
	printf("v x %f / y %f / z %f\n", v.x, v.y, v.z);
}
