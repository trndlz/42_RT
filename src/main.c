/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/10 08:29:15 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mlx_slider(t_env *e)
{
    mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->filter.img.pic, WINY, 0);
    legend(e);
    mlx_key_hook(e->mlx.win, &mykeyhook, e);
    mlx_hook(e->mlx.win, ButtonPress, ButtonPressMask, &mouse_press, e);
    mlx_hook(e->mlx.win, 6, 0, &mouse, e);
    mlx_hook(e->mlx.win, ButtonRelease, ButtonReleaseMask, &mouse_release, e);
}

int		main(int ac, char **av)
{
	t_env *e;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./rt [scene_file]\n", 2);
		return (0);
	}
	if (!(e = init_env()))
		exit_message("Problem while creating environment structure\n");
	if (!init_mlx(&(e->mlx)))
		exit_message("Problem while creating MLX environment\n");
	if (!parser(e, av))
		return (0);
	pthread_mutex_init(&(e->mutex), NULL);
	init_slider(e);
	if (!(create_image(e)))
		exit_message("Problem while creating image\n");
	mlx_hook(e->mlx.win, 2, 3, deal_key, e);
	mlx_slider(e);
	mlx_hook(e->mlx.win, 17, 0, exit_hook, e);
	// mlx_mouse_hook(e->mlx.win, deal_mouse, e);
	mlx_loop(e->mlx.mlx);
	free_all_lists(e);
	free(e);
	return (0);
}
