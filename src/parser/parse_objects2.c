/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/10 16:34:20 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*parse_disc(t_env *e, char *file)
{
	t_obj *disc;

	if (!(disc = default_disc()))
	{
		ft_putstr_fd("Malloc <disc> object failed !\n", 2);
		return (file);
	}
	file = objects_items(disc, file, DISC);
	if (disc->cut && (disc->descartes.y > 0 || disc->cut->descartes.y > 0))
		ft_putstr("Transparent <disc> objects can't be cut !\n");
	else
		obj_add(&e->obj_link, disc);
	return (file);
}

char		*skip_line(char *file)
{
	file = ft_strchr(file, '\n');
	(file) ? file++ : 0;
	return (file);
}
