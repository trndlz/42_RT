/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_release.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 08:19:08 by naminei           #+#    #+#             */
/*   Updated: 2018/08/10 15:18:02 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				initx(t_slider slider, int a)
{
	int legend_nb;

	legend_nb = 0;
	if (a == 0)
		legend_nb = ((float)slider.pos_x \
				- (float)slider.pos_x_zero) * 100 / (LEG / 2);
	else if (a == 1)
		legend_nb = ((int)((float)slider.pos_x \
						- (float)slider.pos_x_zero) * 255 / (LEG / 2));
	return (legend_nb);
}

static float	initx_two(t_slider slider)
{
	return (((float)slider.pos_x - (float)slider.pos_x_zero) / (LEG / 2));
}

static void		button_release(t_env *e, t_vc rgb, t_vc sda)
{
	int i;

	i = -1;
	e->key[1] = 0;
	if (e->filter.activate == 0)
	{
		e->scene.filter_rgb.x = rgb.x;
		e->scene.filter_rgb.y = rgb.y;
		e->scene.filter_rgb.z = rgb.z;
		e->filter.tmp_col_f = rgbtohex(rgb);
	}
	else if (e->filter.activate == 1)
	{
		e->click_obj->col = rgbtohex(rgb);
		e->click_obj->phong.x = sda.x;
		e->click_obj->phong.y = sda.y;
		e->click_obj->phong.z = sda.z;
	}
	if (e->filter.activate == 0)
	{
		while (++i < WINY * WINZ)
			e->imgstr[i] = mix_colors(e->img_ori[i], rgbtohex(e->scene.filter_rgb), (1 - e->filter.intensity));
	}
	else
		create_image(e);
}

int				mouse_release(int button, int x, int y, t_env *e)
{
	t_vc	rgb;
	t_vc	sda;

	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	if (e->mlx.image)
		mlx_destroy_image(e->mlx.mlx, e->mlx.image);
	if (e->filter.img.pic)
		mlx_destroy_image(e->mlx.mlx, e->filter.img.pic);
	if (!(e->mlx.image = mlx_new_image(e->mlx.mlx, WINY, WINZ)))
		return (0);
	if (!(e->filter.img.pic = mlx_new_image(e->mlx.mlx, LEG, WINZ)))
		return (0);
	x = 0;
	y = 0;
	rgb.x = initx(e->filter.sld_r, 1);
	rgb.y = initx(e->filter.sld_g, 1);
	rgb.z = initx(e->filter.sld_b, 1);
	sda.x = initx_two(e->filter.sld_s);
	sda.y = initx_two(e->filter.sld_d);
	sda.z = initx_two(e->filter.sld_a);
	e->filter.intensity = initx_two(e->filter.sld_i);
	if (button)
	{
		e->key[button] = 0;
		button_release(e, rgb, sda);
	}
	draw_all(e);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->filter.img.pic, WINY, 0);
	legend(e);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.image, 0, 0);
	return (0);
}

char			*ft_sjf(char *s1, char *s2, bool first, bool second)
{
	size_t	lt;
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		ret = (ft_strdup(s2));
	else if (!s2)
		ret = (ft_strdup(s1));
	else
	{
		lt = ft_strlen(s1) + ft_strlen(s2) + 1;
		if ((ret = (char*)malloc(sizeof(char) * lt)) == NULL)
			return (NULL);
		ret = ft_strcpy(ret, s1);
		ret = ft_strcat(ret, s2);
	}
	if (first == 1 && s1)
		free(s1);
	if (second == 1 && s2)
		free(s2);
	return (ret);
}
