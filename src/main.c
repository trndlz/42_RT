/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/06 16:25:43 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	t_env *e;

	if (!(e = init_env()))
		exit_message("Problem while creating environment structure\n");
	if (!init_mlx(&(e->mlx)))
		exit_message("Problem while creating MLX environment\n");
	if (!parser(e, ac, av))
		return (0);
	pthread_mutex_init(&(e->mutex), NULL);
	if (!(create_image(e)))
		exit_message("Problem while creating image\n");
	mlx_hook(e->mlx.win, 2, 3, deal_key, e);
	mlx_hook(e->mlx.win, 17, 0, exit_hook, e);
	mlx_mouse_hook(e->mlx.win, deal_mouse, e);
	mlx_loop(e->mlx.mlx);
	free_all_lists(e);
	free(e);
	return (0);
}
