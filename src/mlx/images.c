/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:37:05 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 15:16:56 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		multi_threading_join(t_env *e)
{
	int		i;

	i = -1;
	while (++i < TH_NB)
	{
		if (pthread_join(e->pth[i], NULL) != 0)
		{
			ft_putstr("Error while joining threads\n");
			return (0);
		}
		progression_bar(e, "Threads Joining", 100 * (i + 1) / TH_NB);
	}
	ft_putchar('\n');
	return (1);
}

int		multi_threading(t_env *e)
{
	int		i;
	t_env	copy[TH_NB];

	i = -1;
	while (++i < TH_NB)
	{
		copy[i] = *e;
		copy[i].thread_int = i;
		if (pthread_create(&e->pth[i], NULL, scene_plot, &copy[i]) != 0)
		{
			ft_putstr("Error while creating threads\n");
			return (0);
		}
		progression_bar(e, "Threads processing", 100 * (i + 1) / TH_NB);
	}
	ft_putchar('\n');
	return (multi_threading_join(e));
}

int		create_image(t_env *e)
{
	int b;
	int s;
	int en;

	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	if (e->mlx.image)
		mlx_destroy_image(e->mlx.mlx, e->mlx.image);
	if (!(e->mlx.image = mlx_new_image(e->mlx.mlx, WINY, WINZ)))
		return (0);
	if (!(e->imgstr = (int *)mlx_get_data_addr(e->mlx.image, &b, &s, &en)))
		return (0);
	if (!multi_threading(e))
		return (0);
	if (e->scene.blinding_lights)
		blinding_lights(e);
	if (e->scene.antialias)
		antialias(e->imgstr);
	if (e->scene.filter == CARTOON)
		if ((!cartooning(e)))
			ft_putstr("Cartoon effect needs more colorful scenes\n");
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.image, 0, 0);
	return (1);
}

int		exit_hook(int k, t_env *e)
{
	if (k)
	{
		pthread_mutex_lock(&(e->mutex));
		exit(1);
	}
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
