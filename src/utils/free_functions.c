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

void		free_color_tab(int **tab, int y)
{
	while (y)
	{
		free(tab[y - 1]);
		y--;
	}
	free(tab);
}

void		free_size_obj(int *size, t_obj *obj)
{
	free(size);
	free(obj);
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

void		free_all_lists(t_env *e)
{
	clear_list(e->obj_link);
	clear_list(e->light_link);
	clear_list(e->cut_link);
}
