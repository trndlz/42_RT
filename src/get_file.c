#include "rtv1.h"

int ft_htod(char c)
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

int ft_htoi(char *str)
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
		{
			color = ft_htod(str[i]) + color * 16;
		}
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

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
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
	else
		return (0);
}

void error_messages(int error)
{
	if (error == 1)
		printf("Some objects do not have good amount of attributes\n");
	if (error == 2)
		printf("Some objects have an unknown name\n Choose from :\n- eye\n- light\n- sphere\n- cylinder\n- plane\n- cone\n");
	if (error == 3)
		printf("Some objects have an invalid color\nColors must be written in hexadecimal format and not exceed max value 0XFFFFFF\n");
	if (error == 4)
		printf("Some objects length is invalid (careful : must be positive)\n");
	if (error == 5)
		printf("Some objects coordinates are invalid\n");
}

t_obj	*attribute_object(char **tab_values)
{
	t_obj *scene;
	int error;

	if (!(scene = malloc(sizeof(t_obj))))
		return (NULL);
	error = check_value(tab_values);
	if (check_value(tab_values) > 0)
	{
		error_messages(error);
		return (NULL);
	}
	scene->type = name_type(tab_values[0]);
	if (scene->type != 5)
	{
		scene->col = ft_htoi(tab_values[7]);
		scene->size = (double)ft_atoi(tab_values[8]);
		scene->rot = init_vc((double)ft_atoi(tab_values[4]), (double)ft_atoi(tab_values[5]), (double)ft_atoi(tab_values[6]));
	}
	scene->pos = init_vc((double)ft_atoi(tab_values[1]), (double)ft_atoi(tab_values[2]), (double)ft_atoi(tab_values[3]));
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

void	attribute_scene(int fd, t_env *e)
{
	char	*str;
	char	**tab_values;
	t_obj		*tmp;

	while (get_next_line(fd, &str))
	{
		if (str[0] != '#' && str[0] != '\n')
		{
			str = tabtospace(str);
			tab_values = ft_strsplit(str, ' ');
			tmp = attribute_object(tab_values);
			if (tmp->type != 5)
				obj_add(&e->link, tmp);
			else
			{
				e->light = tmp;
				printf(" > light x %f y %f z %f\n", e->light->pos.x, e->light->pos.y, e->light->pos.z);
			}
		}
	}
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
