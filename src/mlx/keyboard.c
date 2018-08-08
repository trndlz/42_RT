/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:47:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/06 16:10:08 by jostraye         ###   ########.fr       */
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
}

int		deal_key(int key, t_env *e)
{
	if (key == 35)
	{
		pthread_mutex_lock(&(e->mutex));
		create_bmp_file(e->imgstr);
		pthread_mutex_unlock(&(e->mutex));
	}
	else if (key == 53)
	{
		pthread_mutex_lock(&(e->mutex));
		mlx_destroy_image(e->mlx.mlx, e->mlx.image);
		mlx_destroy_window(e->mlx.mlx, e->mlx.win);
		pause();
		exit(1);
	}
	else
	{
		translation(key, e);
		rotation(key, e);
		create_image(e);
	}
	return (0);
}

t_obj	*click_to_object(t_env *e, int y, int z)
{
	t_hit_rec	hit_rec;
	t_ray		ray;

	ray = create_ray(y, z, e->eye_rot, e->eye_lookfrom);
	if (nearest_node(e, ray, &hit_rec))
		return (hit_rec.hit_obj);
	return (NULL);
}

int		deal_mouse(int k, int y, int z, t_env *e)
{
	if (y >= 0 && z >= 0 && y <= WINY && z <= WINZ && e)
	{
		if (k == 1)
		{
			ft_putstr("y -> ");
			ft_putnbr(y);
			ft_putstr(" / z -> ");
			ft_putnbr(z);
			ft_putchar('\n');
		}
	}
	return (0);
}
