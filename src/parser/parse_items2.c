/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:37 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

char			*parse_int(char *file, unsigned int *d)
{
	int		check;

	if ((check = sscanf(file, "%*s %u \n", (d)) != 1))
		return (parser_error("Invalid value !\n", file));
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}

char			*parse_color(char *file, int *col)
{
	int		check;
	char	colstr[12];

	if ((check = sscanf(file, "%*s %10s\n", colstr) != 1))
		return (parser_error("Invalid color values\n", file));
	*col = ft_htoi(colstr);
	if (!(file = ft_strchr(file, '\n')))
		return (NULL);
	file++;
	return (file);
}
