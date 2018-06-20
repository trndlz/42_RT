/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:37:05 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 16:46:35 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			multi_threading(t_env *e)
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

void		create_image(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	e->image = mlx_new_image(e->mlx, WINY, WINZ);
	e->imgstr = (int *)mlx_get_data_addr(e->image, &e->bpp, &e->s_l,
			&e->endian);
	multi_threading(e);
	mlx_put_image_to_window(e->mlx, e->win, e->image, 0, 0);
	mlx_destroy_image(e->mlx, e->image);
}

void		draw_point(t_env *e, int x, int y, unsigned int color)
{
	int i;

	i = (x + ((y * e->s_l) / 4));
	if (i >= 0 && i < (WINY * WINZ))
		e->imgstr[i] = color;
}
