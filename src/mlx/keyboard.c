/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:47:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 09:40:34 by nozanne          ###   ########.fr       */
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

void	perturb(int key, t_env *e)
{
	if (e->click_obj && key == 82)
		e->click_obj->perturb = 0;
	if (e->click_obj && key == 83)
		e->click_obj->perturb = 1;
	if (e->click_obj && key == 84)
		e->click_obj->perturb = 2;
	if (e->click_obj && key == 85)
		e->click_obj->perturb = 3;
	if (e->click_obj && key == 86)
		e->click_obj->perturb = 4;
}

int		deal_key(int key, t_env *e)
{
	if (key)
		e->key[key] = 1;
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
		exit(1);
	}
	else
	{
		translation(key, e);
		rotation(key, e);
		perturb(key, e);
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
