/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:43 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			t_calculator(double a, double b)
{
	if (a < D_ZERO)
	{
		if (b > D_ZERO)
			return (b);
		return (-1);
	}
	if (b < D_ZERO)
	{
		if (a > D_ZERO)
			return (a);
		return (-1);
	}
	if (a < b)
		return (a);
	return (b);
}

double			quadratic_solver(t_hit_rec *hit, t_vc abc)
{
	double d;
	double t1;
	double t2;

	d = (double)car(abc.y) - (double)(4.0 * (abc.x * abc.z));
	if (d < 0)
		return (-1);
	t1 = (-abc.y + sqrt(d)) / (2.0 * abc.x);
	t2 = (-abc.y - sqrt(d)) / (2.0 * abc.x);
	hit->t1 = (t1 < t2) ? t1 : t2;
	hit->t2 = (t1 < t2) ? t2 : t1;
	return (t_calculator(t1, t2));
}
