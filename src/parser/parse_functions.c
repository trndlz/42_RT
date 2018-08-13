/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:36 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*skip_whitespace(char *file)
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
