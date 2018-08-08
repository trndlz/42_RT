/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:12:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/19 21:25:05 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void		clear_list(t_obj *head)
{
	t_obj *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void		progression_bar(t_env *e, char *str, int i)
{
	fprintf(stderr, "%s |%.*s%.*s| %d\r", str, (int)(i / 2),
	e->eq, (int)(50 - i / 2), e->sp, i);
	fflush(stdout);
}

void		free_all_lists(t_env *e)
{
	clear_list(e->obj_link);
	clear_list(e->light_link);
	clear_list(e->cut_link);
}
