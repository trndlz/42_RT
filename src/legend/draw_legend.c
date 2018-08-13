/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:14:10 by naminei           #+#    #+#             */
/*   Updated: 2018/08/13 09:59:06 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		draw_legend(t_env *e, int x, int y, char *legend)
{
	if (legend)
		mlx_string_put(e->mlx.mlx, e->mlx.win, x, y, 0xded9df, legend);
	else
		exit_message("malloc error\n");
	free(legend);
}

static char		*inter_leg(t_slider slider)
{
	return (ft_sjf(ft_itoa(initx(slider, 0) \
			/ 100), ft_sjf(".", ft_itoa(initx(slider, 0) % 100), 0, 1), 1, 1));
}

static void		legend_activate_yes(t_env *e, char *leg)
{
	leg = ft_sjf("Spec: ", inter_leg(e->filter.sld_s), 0, 1);
	draw_legend(e, WINY + 270, 390, leg);
	leg = ft_sjf("Diff: ", inter_leg(e->filter.sld_d), 0, 1);
	draw_legend(e, WINY + 270, 440, leg);
	leg = ft_sjf("Amb: ", inter_leg(e->filter.sld_a), 0, 1);
	draw_legend(e, WINY + 270, 490, leg);
	mlx_string_put(e->mlx.mlx, e->mlx.win, WINY \
		+ 50, 50, 0xded9df, "Click HERE to change RGB Filters");
	leg = ft_sjf("Perturbation:  ", ft_itoa(e->click_obj->perturb), 0, 1);
	draw_legend(e, WINY + 70, 540, leg);
}

static void		legend_activate(t_env *e)
{
	char	*leg;

	leg = NULL;
	if (e->filter.activate == 0)
	{
		leg = ft_sjf("I: ", inter_leg(e->filter.sld_i), 0, 1);
		draw_legend(e, WINY + 270, 340, leg);
		mlx_string_put(e->mlx.mlx, e->mlx.win, WINY \
			+ 70, 40, 0xded9df, "Click on an object to modify");
		mlx_string_put(e->mlx.mlx, e->mlx.win, WINY \
			+ 110, 70, 0xded9df, "its caracteristics");
	}
	else if (e->filter.activate == 1)
		legend_activate_yes(e, leg);
}

void			legend(t_env *e)
{
	char	*leg;

	leg = ft_sjf("R: ", ft_itoa(initx(e->filter.sld_r, 1)), 0, 1);
	draw_legend(e, WINY + 270, 190, leg);
	leg = ft_sjf("G: ", ft_itoa(initx(e->filter.sld_g, 1)), 0, 1);
	draw_legend(e, WINY + 270, 240, leg);
	leg = ft_sjf("B: ", ft_itoa(initx(e->filter.sld_b, 1)), 0, 1);
	draw_legend(e, WINY + 270, 290, leg);
	mlx_string_put(e->mlx.mlx, e->mlx.win, WINY \
		+ 130, 140, 0xded9df, write_obj(e->click_obj));
	legend_activate(e);
}
