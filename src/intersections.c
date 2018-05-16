/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:03:32 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/16 16:06:12 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double          inter_sph(t_env *e, t_vc tmp, t_vc ray, t_obj *obj)
{
    double d;
    double t1;
    double t2;

    e->a = vec_squ_sum(&ray);
    e->b = 2 * vec_cross_prod(&tmp, &ray);
    e->c = vec_squ_sum(&tmp) - car(obj->size);
    d = car(e->b) - 4 * e->a * e->c;
    if (d < 0)
        return (-1);
    t1 = (-e->b + sqrt(d)) / (2 * e->a);
    t2 = (-e->b - sqrt(d)) / (2 * e->a);
    if (d == 0)
        return (t1);
    else
        return (t1 < t2 ? t1 : t2);
}

double          inter_cone(t_env *e, t_vc tmp, t_vc ray, t_obj *obj)
{
    double d;
    double t1;
    double t2;
    double k;

    vec_normalize(&obj->rot);
    k = 1 + car(tan(obj->size));
    e->a = vec_cross_prod(&ray, &ray)
        - k * car(vec_cross_prod(&ray, &obj->rot));
    e->b = 2 * (vec_cross_prod(&ray, &tmp)
        - k * vec_cross_prod(&ray, &obj->rot)
        * vec_cross_prod(&tmp, &obj->rot));
    e->c = vec_cross_prod(&tmp, &tmp)
        - k * car(vec_cross_prod(&tmp, &obj->rot));
    d = car(e->b) - 4 * e->a * e->c;
    if (d < 0.00001)
        return (-1);
    t1 = (-e->b + sqrt(d)) / (2 * e->a);
    t2 = (-e->b - sqrt(d)) / (2 * e->a);
    if (d == 0)
        return (t1);
    else
        return (t1 < t2 ? t1 : t2);
}

double          inter_plane(t_vc tmp, t_vc ray, t_obj *obj)
{
    double t;

    vec_normalize(&obj->rot);
    t = -vec_cross_prod(&tmp, &obj->rot) / vec_cross_prod(&ray, &obj->rot);
    if (t < 0.00001)
        return (-1);
    return (t);
}

double          inter_cyl(t_env *e, t_vc tmp, t_vc ray, t_obj *obj)
{
    double d;
    double t1;
    double t2;

    vec_normalize(&obj->rot);
    e->a = vec_cross_prod(&ray, &ray) - car(vec_cross_prod(&ray, &obj->rot));
    e->b = 2 * (vec_cross_prod(&ray, &tmp)
        - vec_cross_prod(&ray, &obj->rot) * vec_cross_prod(&tmp, &obj->rot));
    e->c = vec_cross_prod(&tmp, &tmp)
        - car(vec_cross_prod(&tmp, &obj->rot)) - car(obj->size);
    d = car(e->b) - 4 * e->a * e->c;
    if (d < 0.00001)
        return (-1);
    t1 = (-e->b + sqrt(d)) / (2 * e->a);
    t2 = (-e->b - sqrt(d)) / (2 * e->a);
    if (d == 0)
        return (t1);
    else
        return (t1 < t2 ? t1 : t2);
}
