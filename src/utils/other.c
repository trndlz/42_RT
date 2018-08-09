/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:12:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 15:41:04 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		progression_bar(t_env *e, char *str, int i)
{
	fprintf(stderr, "%s |%.*s| %d\r", str, (int)(i / 4), e->eq, i);
	fflush(stdout);
}

int			err_malloc_texture(int *size, t_obj *obj)
{
	ft_putstr_fd("Texture file data could not be loaded !\n", 2);
	free_size_obj(size, obj);
	return (0);
}