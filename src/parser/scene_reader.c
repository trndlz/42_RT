/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*read_scene(int fd, char **av)
{
	char	*file;
	char	buf[2048];
	int		size;
	int		ret;

	size = 0;
	while ((ret = read(fd, buf, 2048)) > 0)
		size += ret;
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (!(file = (char*)malloc(sizeof(char) * (size + 1))))
	{
		if (file)
			free(file);
		return (NULL);
	}
	if (read(fd, file, size) < 0)
	{
		if (file)
			free(file);
		return (NULL);
	}
	file[size] = '\0';
	return (file);
}

char		*parser_error(char *message, char *line)
{
	char *end;

	end = ft_strchr(line, '\n');
	ft_putstr_fd("RT scene file error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("On line:\n", 2);
	if (end)
		write(2, line, end - line);
	else
		ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}



char		*parse_scene(t_env *e, char *file)
{
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("+antialias\n", file, 11) == 0)
		{
			e->scene.antialias = 1;
			file = file + 11;
		}

		else if (ft_strncmp("+blinding_lights\n", file, 17) == 0)
		{
			e->scene.blinding_lights = 1;
			file = file + 17;
		}
		else if (ft_strncmp("[filter] ", file, 9) == 0)
			file = parse_filter(file, &(e->scene.filter));
		else
			break ;
	}
	return (file);
}


void		create_scene(t_env *e, char *file)
{
	while (file && *file)
	{
		file = skip_whitespace(file);
		if (ft_strncmp("<eye>\n", file, 6) == 0)
			file = parse_eye(e, file + 6);
		else if (ft_strncmp("<light>\n", file, 8) == 0)
			file = parse_light(e, file + 8);
		else if (ft_strncmp("<sphere>\n", file, 9) == 0)
			file = parse_sphere(e, file + 9);
		else if (ft_strncmp("<cone>\n", file, 7) == 0)
			file = parse_cone(e, file + 7);
		else if (ft_strncmp("<cylinder>\n", file, 11) == 0)
			file = parse_cylinder(e, file + 11);
		else if (ft_strncmp("<plane>\n", file, 8) == 0)
			file = parse_plane(e, file + 8);
		else if (ft_strncmp("<paraboloid>\n", file, 13) == 0)
			file = parse_paraboloid(e, file + 13);
		else if (ft_strncmp("<scene>\n", file, 8) == 0)
			file = parse_scene(e, file + 8);
		else
		{
			file = ft_strchr(file, '\n');
			if (file)
				file++;
		}
	}
}

int			parser(t_env *e, int ac, char **av)
{
	char	*file;
	int		fd1;
	int		fd2;

	if (ac < 2)
	{
		ft_putstr_fd("Usage:\n", 2);
		ft_putstr_fd("./rt [scene_file]\n", 2);
		return (0);
	}
	fd1 = open(av[1], O_DIRECTORY);
	fd2 = open(av[1], O_RDONLY);
	if (fd1 > 0 || fd2 < 0)
	{
		ft_putstr_fd("Cannot open scene file.\n", 2);
		return (0);
	}
	file = read_scene(fd2, av);
	create_scene(e, file);
	free(file);
	close(fd1);
	close(fd2);
	return (1);
}
