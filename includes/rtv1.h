/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/12 15:40:36 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# define WINX 1000
# define WINY 500
# define WIND 20
# define FOV 100

typedef struct		s_vc
{
	double			x;
	double			y;
	double			z;
}					t_vc;

typedef struct		s_vport
{
	t_vc			up_vec;
	t_vc			cam_dir;
	t_vc			right;
	t_vc			vp_up_left;
	t_vc			up;
	double			vp_width;
	double			vp_height;
	double			vp_dist;
}					t_vport;

typedef struct		s_obj
{
	int				type;
	t_vc			rot;
	t_vc			pos;
	double			size;
	double			ks;
	double			ka;
	double			kd;
	int				color[3];
	struct s_obj	*next;
}					t_obj;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*image;
	int				*imgstr;
	int				bpp;
	int				s_l;
	int				endian;
	int				x;
	int				y;
	double			a;
	double			b;
	double			c;
	double			t;
	double			t1;
	double			t2;
	double			cost;
	double			cost2;
	t_vport 			*vport;
	t_vc			tmp;
	t_vc			ve;
	t_vc			ray;
	t_vc			ray_dir;
	t_vc			eye_pos;
	t_vc			eye_rot;
	t_vc			plan;
	t_obj			*light;
	t_vc			norm;
	t_vc			n;
	t_vc			lm;
	t_vc			rm;
	t_vc			v;
	t_vc			k;
	t_vc			i;
	t_vc			j;
	t_vc			offset;
	t_obj			*link;
}					t_env;

void				create_image(t_env *e);
void				draw_point(t_env *e, int x, int y, unsigned int color);
void				scene_plot(t_env *e);

/*
** MATHS
*/

double				car(double a);
void				rot_x(t_vc *vc, int t);
void				rot_y(t_vc *vc, int t);
void				rot_z(t_vc *vc, int t);
void				rot_all_axis(t_vc *vc, t_obj *obj);
double				vec_squ_sum(t_vc *v1);
t_vc				vec_add(t_vc *v1, t_vc *v2);
t_vc				vec_sub(t_vc *v1, t_vc *v2);
t_vc				vec_croise(t_vc *v1, t_vc *v2);
double				vec_x(t_vc *v1, t_vc *v2);
double				vec_mod(t_vc *v);
void				vec_norm(t_vc *v);
t_vc				vec_mult(t_vc *v, double x);
double				vec_dot(t_vc *v1, t_vc *v2);

/*
** SHAPES INTERSECTIONS
*/

double				inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				inter_plane(t_obj *obj, t_vc ray, t_vc offset);
double				inter_cyl(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				inter_sph(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				quadratic_solver(t_env *e);

/*
** KEYBOARD
*/

void	translation(int key, t_env *e);
int		deal_key(int key, t_env *e);
int		deal_mouse(int k, int x, int y, t_env *e);

/*
** LIGHTING
*/

void				lighting_vectors(t_env *e, t_obj *obj);

/*
** COLORS
*/

unsigned long		rgb_to_hexa(t_obj *obj, t_env *e);

/*
** STRUCTURES INITIALIZATION
*/

t_env				*init_env(void);
t_vc				init_vc(double x, double y, double z);

/*
** OBJECTS
*/

void				obj_add(t_obj **beg, t_obj *n);
t_obj				*new_sphere(void);
t_obj				*new_cylinder(void);
t_obj				*new_cone(void);
t_obj				*new_plane(void);
t_obj				*new_light(void);

#endif
