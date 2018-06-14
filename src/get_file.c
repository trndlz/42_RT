/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:55:28 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/14 16:09:50 by tmervin          ###   ########.fr       */
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

int		ft_htod(char c)
{
	if (ft_isdigit(c))
		return ((int)(c - 48));
	else if ('A' <= 'c' && 'F' >= c)
		return ((int)(c - 55));
	else if ('a' <= c && 'f' >= c)
 		return ((int)(c - 87));
	else
		return (-1);
}

int		ft_htoi(char *str)
{
	int i;
	int color;

	color = 0;
	i = 2;
	while (str[0] != '0' && (str[1] != 'x' || str[1] != 'X'))
		return (-1);
	while (str[i])
	{
		if (ft_htod(str[i]) >= 0)
			color = ft_htod(str[i]) + color * 16;
		i++;
	}
	return (color);
}

int ft_iscolor(char *str)
{
	int color;

	color = ft_htoi(str);
	if (color < 0 || color > 0xFFFFFF)
		return (1);
	else
		return (0);
}

int ft_isnumber(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (1);
	}
	return (0);
}

int check_value(char **str)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (str[i])
		i++;
	if (i != 12)
		return (1);
	while (j < 10 && str[i])
	{
		if (ft_isnumber(str[j]))
			return (3);
            // A TESTER AVEC UNE VALEUR TROP GRANDE POUR UN INT
		j++;
	}
	if (ft_iscolor(str[10]))
		return (3);
	if (ft_isnumber(str[11]) || ft_atoi(str[11]) < 0)
		return (4);
	return (0);
}



void error_messages(int error)
{
	if (error == 1)
		exit_message("Some objects do not have good amount of attributes\n");
	if (error == 2)
		exit_message("Some objects have an unknown name\n Choose from :\n- eye\n- light\n- sphere\n- cylinder\n- plane\n- cone\n");
	if (error == 3)
		exit_message("Some objects have an invalid color\nColors must be written in hexadecimal format and not exceed max value 0XFFFFFF\n");
	if (error == 4)
		exit_message("Some objects length is invalid (careful : must be positive)\n");
	if (error == 5)
		exit_message("Some objects coordinates are invalid\n");
	if (error == 6)
		exit_message("Defining a light AND an eye position AND rotation is mandatory !\n");
}

t_obj	*attribute_object(char **tab_values)
{
	t_obj *scene;
	int error;

	if (!(scene = malloc(sizeof(t_obj))))
		return (NULL);
	error = check_value(tab_values);
	if (check_value(tab_values) > 0)
		error_messages(error);
	if (!(scene->type = name_type(tab_values[0])))
		error_messages(2);
	if (scene->type != 5)
	{
		scene->col = ft_htoi(tab_values[7]);
		scene->size = (double)ft_atoi(tab_values[8]);
	}
	scene->pos = init_vc((double)ft_atoi(tab_values[1]), (double)ft_atoi(tab_values[2]), (double)ft_atoi(tab_values[3]));
	scene->rot = init_vc((double)ft_atoi(tab_values[4]), (double)ft_atoi(tab_values[5]), (double)ft_atoi(tab_values[6]));
	scene->next = NULL;

	return (scene);
}

char	*tabtospace(char *str)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == '\t')
			str[j] = ' ';
	}
	return (str);
}

void	free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	attribute_scene(int fd, t_env *e)
{
	char	*str;
	char	**tab_values;
	t_obj	*tmp;
	int		err;

	err = 0;
	while (get_next_line(fd, &str))
	{
		if (str[0] != '#' && str[0] != '\n')
		{
			str = tabtospace(str);
			tab_values = ft_strsplit(str, ' ');
			tmp = attribute_object(tab_values);

			if (tmp->type >= 1 && tmp->type <= 4)
				obj_add(&e->link, tmp);
			else if (tmp->type == 5)
				e->light = tmp;
			else if (tmp->type == 6)
			{
				e->eye_lookfrom = tmp->pos;
				e->eye_rot = tmp->rot;
				err++;
			}
			free_split(tab_values);
		}
		free(str);
	}
	free(tmp);
	if (!e->light || err == 0)
		error_messages(6);
}


void	get_scene(char **argv, t_env *e)
{
	int			fd;

	// if (argv[1] == NULL)
	// {
	// 	printf("The configuration file is empty\n");
	// 	return (NULL);
	// }
    // On veut verifer que le fichier ne soit pas vide
	if ((fd = open(argv[1], O_RDONLY)) >= 0)
		attribute_scene(fd, e);
}
