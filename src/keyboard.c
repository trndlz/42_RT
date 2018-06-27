/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:47:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/27 13:59:03 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	translation(int key, t_env *e)
{
	if (key == 34)
		e->eye_lookfrom.x += 100;
	if (key == 38)
		e->eye_lookfrom.y += 100;
	if (key == 32)
		e->eye_lookfrom.z += 100;
	if (key == 40)
		e->eye_lookfrom.x -= 100;
	if (key == 37)
		e->eye_lookfrom.y -= 100;
	if (key == 31)
		e->eye_lookfrom.z -= 100;
	ft_putstr("\nEYE COORDINATES : X : ");
	ft_putnbr(e->eye_lookfrom.x);
	ft_putstr(" | Y : ");
	ft_putnbr(e->eye_lookfrom.y);
	ft_putstr(" | Z : ");
	ft_putnbr(e->eye_lookfrom.z);
}

void	rotation(int key, t_env *e)
{
	if (key == 0)
		e->eye_rot.x += 5;
	if (key == 13)
		e->eye_rot.y += 5;
	if (key == 14)
		e->eye_rot.z += 5;
	if (key == 2)
		e->eye_rot.x -= 5;
	if (key == 1)
		e->eye_rot.y -= 5;
	if (key == 12)
		e->eye_rot.z -= 5;
	ft_putstr("\nEYE ROTATION : X : ");
	ft_putnbr(e->eye_rot.x);
	ft_putstr(" | Y : ");
	ft_putnbr(e->eye_rot.y);
	ft_putstr(" | Z : ");
	ft_putnbr(e->eye_rot.z);
}

int		deal_key(int key, t_env *e)
{
	if (key == 53)
	{
		create_bmp(e->imgstr, (unsigned int)WINY * WINZ, e);
		mlx_destroy_window(e->mlx, e->win);
		exit(1);
	}
	translation(key, e);
	rotation(key, e);
	create_image(e);
	return (0);
}

int		deal_mouse(int k, int y, int z, t_env *e)
{
	if (y >= 0 && z >= 0 && y <= WINY && z <= WINZ && e)
	{
		if (k == 1)
		{
			printf("y %d / z %d\n", y, z);
		}
	}
	return (0);
}
