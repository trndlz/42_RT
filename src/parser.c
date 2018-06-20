/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:55:28 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/20 16:41:36 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		name_type(char *str)
{
	if (!ft_strcmp(str, "sphere"))
		return (1);
	else if (!ft_strcmp(str, "cylinder"))
		return (2);
	else if (!ft_strcmp(str, "cone"))
		return (3);
	else if (!ft_strcmp(str, "plane"))
		return (4);
	else if (!ft_strcmp(str, "light"))
		return (5);
	else if (!ft_strcmp(str, "eye"))
		return (6);
	else
		return (0);
}

t_obj	*attribute_object(char **tab_values)
{
	t_obj	*scene;
	int		error;

	if (!(scene = malloc(sizeof(t_obj))))
		return (NULL);
	error = check_value(tab_values);
	if (check_value(tab_values) > 0)
		error_messages(error);
	scene->type = name_type(tab_values[0]);
	scene->pos = init_vc((double)ft_atoi(tab_values[1]),
		(double)ft_atoi(tab_values[2]), (double)ft_atoi(tab_values[3]));
	scene->rot = init_vc((double)ft_atoi(tab_values[4]),
		(double)ft_atoi(tab_values[5]), (double)ft_atoi(tab_values[6]));
	scene->next = NULL;
	if (scene->type == 6)
		return (scene);
	scene->col = ft_htoi(tab_values[7]);
	if (scene->type == 5)
		return (scene);
	scene->size = (double)ft_atoi(tab_values[8]);
	scene->coef = init_vc(ft_atof(tab_values[9]),
		ft_atof(tab_values[10]), ft_atof(tab_values[11]));
	return (scene);
}

void	create_objects(t_env *e, char **tab_values)
{
	t_obj *tmp;

	tmp = attribute_object(tab_values);
	if (tmp->type >= 1 && tmp->type <= 4)
		obj_add(&e->obj_link, tmp);
	else if (tmp->type == 5)
		obj_add(&e->light_link, tmp);
	else if (tmp->type == 6)
	{
		e->eye_lookfrom = init_vc(tmp->pos.x, tmp->pos.y, tmp->pos.z);
		e->eye_rot = init_vc(tmp->rot.x, tmp->rot.y, tmp->rot.z);
		e->nb_eye++;
		free(tmp);
	}
}

int		attribute_scene(int fd, t_env *e)
{
	char	*str;
	char	**tab_values;

	while (get_next_line(fd, &str) == 1)
	{
		if (str[0] != '#' && ft_strlen(str) > 1)
		{
			str = tabtospace(str);
			if (!(tab_values = ft_strsplit(str, ' ')))
				return (0);
			create_objects(e, tab_values);
			free_split(tab_values);
		}
		free(str);
	}
	free(str);
	close(fd);
	if (e->nb_eye != 1)
		error_messages(6);
	return (1);
}

int		parser(char **av, t_env *e)
{
	int	fd;

	fd = open(av[1], O_DIRECTORY);
	if (fd > 0)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	else
	{
		if (!attribute_scene(fd, e))
			return (0);
	}
	return (1);
}
