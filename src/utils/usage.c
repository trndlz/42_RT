/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:57:03 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:48 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_usage(void)
{
	ft_putstr_fd("Usage:\n", 2);
	ft_putstr_fd("./rtv1 scene_file\n", 2);
	exit(1);
}

void		exit_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void		replace_char(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str) && !ft_isdigit(*str))
			*str = ' ';
		str++;
	}
}
