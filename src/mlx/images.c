/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:37:05 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/24 17:15:16 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		multi_threading(t_env *e)
{
	int		i;
	t_env	copy[TH_NB];

	i = 0;
	while (i < TH_NB)
	{
		copy[i] = *e;
		copy[i].thread_int = i;
		pthread_create(&e->pth[i], NULL, scene_plot, &copy[i]);
		i++;
	}
	while (i--)
		pthread_join(e->pth[i], NULL);
	return (0);
}

int		create_image(t_env *e)
{
	int b;
	int s;
	int en;

	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	if (!(e->mlx.image = mlx_new_image(e->mlx.mlx, WINY, WINZ)))
		return (0);
	if (!(e->imgstr = (int *)mlx_get_data_addr(e->mlx.image, &b, &s, &en)))
		return (0);
	multi_threading(e);
	if (e->scene.blinding_lights)
		blinding_lights(e);
	if (e->scene.antialias)
		antialias(e->imgstr);
	if (e->scene.filter == CARTOON)
		if ((!cartooning(e)))
			return (0);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.image, 0, 0);
	return (1);
}

void	draw_point(t_env *e, int x, int y, unsigned int color)
{
	int i;

	i = (x + (y * WINZ));
	pthread_mutex_lock(&(e->mutex));
	if (i >= 0 && i < (WINY * WINZ))
		e->imgstr[i] = color;
	pthread_mutex_unlock(&(e->mutex));
}