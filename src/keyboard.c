/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:47:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 11:43:29 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	translation(int key, t_env *e)
{
	printf("KEY  %d \n", key);
	e += 0;
}

int		deal_key(int key, t_env *e)
{
	if (key == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(1);
	}
	translation(key, e);
	create_image(e);
	return (0);
}

int		deal_mouse(int k, int y, int z, t_env *e)
{
	if (y >= 0 && z >= 0 && y <= WINY && z <= WINZ && e)
	{
		if (k == 1)
		{
			printf("y %d / z %d\n", y, z);
		}
	}
	return (0);
}
