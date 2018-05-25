/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:47:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/25 11:33:26 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	translation(int key, t_env *e)
{
	if (key == 0)
		e->light->pos.x += 25;
	if (key == 13)
		e->light->pos.y += 25;
	if (key == 14)
		e->light->pos.z += 25;
	if (key == 2)
		e->light->pos.x -= 25;
	if (key == 1)
		e->light->pos.y -= 25;
	if (key == 12)
		e->light->pos.z -= 25;
}

int		deal_key(int key, t_env *e)
{
	printf("light x %f y %f z %f\n", e->light->pos.x, e->light->pos.y, e->light->pos.z);
	if (key == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(1);
	}
	translation(key, e);
	create_image(e);
	return (0);
}

int		deal_mouse(int k, int x, int y, t_env *e)
{
	if (x >= 0 && y >= 0 && x <= WINX && y <= WINY && e)
	{
		if (k == 1)
		{
			printf("x %d / y %d\n", x, y);
		}
	}
	return (0);
}
