/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:04:59 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/16 15:59:37 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->mlx = mlx_init()))
        return (NULL);
	if (!(e->win = mlx_new_window(e->mlx, WINW, WINH, "RTv1")))
        return (NULL);
    e->eye = init_vc(-200, 40, 40);
	return (e);
}

t_vc        init_vc(double x, double y, double z)
{
    t_vc vc;

    vc.x = x;
    vc.y = y;
    vc.z = z;
    return (vc);
}
