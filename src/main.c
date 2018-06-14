/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/14 17:30:35 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int             main(int ac, char **av)
{
    t_env *e;

	if (ac != 2)
		ft_usage();
    if (!(e = init_env()))
    	exit_message("Problem while creating environment structure\n");
	e->link = NULL;

    get_scene(av, e);
	create_image(e);
	mlx_hook(e->win, 2, 3, deal_key, e);
	//mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
    return (0);
}
