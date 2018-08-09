/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:12:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/19 21:25:05 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		progression_bar(t_env *e, char *str, int i)
{
	fprintf(stderr, "%s |%.*s| %d\r", str, (int)(i / 4), e->eq, i);
	fflush(stdout);
}
