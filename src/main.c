/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 11:57:06 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void clear_list(t_obj *head)
{
   t_obj *tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

int             main(int ac, char **av)
{
    t_env *e;

	if (ac != 2)
		ft_usage();
    if (!(e = init_env()))
    	exit_message("Problem while creating environment structure\n");
	e->obj_link = NULL;
	e->light_link = NULL;
    get_scene(av, e);
	// light_list = e->light_link;
	// while (light_list)
	// {
	// 	printf("light main x %f y %f z %f\n", light_list->pos.x, light_list->pos.y, light_list->pos.z);
	// 	light_list = light_list->next;
	// }
	create_image(e);
	mlx_hook(e->win, 2, 3, deal_key, e);
	//mlx_hook(e->win, 6, 1L << 6, mouse_move, e);
    mlx_mouse_hook(e->win, deal_mouse, e);
    mlx_loop(e->mlx);
	//clear_list(e->obj_link);
	//free(e);
    return (0);
}
