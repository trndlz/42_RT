/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/06/14 16:58:39 by jostraye         ###   ########.fr       */
=======
/*   Updated: 2018/06/14 15:37:52 by tmervin          ###   ########.fr       */
>>>>>>> 8900dd3b7dbedb74d887193ff147d6e53e7bf56f
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# define WINY 1000
# define WINZ 1000
# define FOV 1000

typedef struct		s_vc
{
	double			x;
	double			y;
	double			z;
}					t_vc;

typedef struct		s_obj
{
	int				type;
	t_vc			rot;
	t_vc			pos;
	int				col;
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
	int				y;
	int				z;
	double			t;
	double			s;
	double			a;
	double			b;
	double			c;
	double			t1;
	double			t2;
	double			cost;
	t_vc			tmp;
	t_vc			ray;
	t_vc			eye_lookfrom;
	t_vc			eye_rot;
	t_vc			plan;
	t_obj			*light;
	t_vc			norm;
	t_vc			n;
	t_vc			lm;
	t_vc			rm;
	t_vc			v;
	t_vc			k;
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
t_vc				rot_x(t_vc vc, int t);
t_vc				rot_y(t_vc vc, int t);
t_vc				rot_z(t_vc vc, int t);
t_vc				rot_all_axis(t_vc vc, t_vc obj);
t_vc				rot_all_axis_inv(t_vc vc, t_vc obj);
double				vec_squ_sum(t_vc v1);
t_vc				vec_add(t_vc *v1, t_vc *v2);
t_vc				vec_sub(t_vc v1, t_vc v2);
t_vc				vec_croise(t_vc *v1, t_vc *v2);
double				vec_x(t_vc v1, t_vc v2);
double				vec_mod(t_vc v);
void				vec_norm(t_vc v);
t_vc				vec_mult(t_vc v, double x);
double				vec_dot(t_vc v1, t_vc v2);

/*
** SHAPES INTERSECTIONS
*/

double				inter_cone(t_env *e, t_obj *obj, t_vc ray, t_vc offset);
double				inter_plane(t_vc ray, t_vc offset);
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
t_obj				*new_sphere(int k);
t_obj				*new_cylinder(int k);
t_obj				*new_cone(void);
t_obj				*new_plane(int a, int b, int c);
t_obj				*new_light(void);

/*
** ERROR MGT
*/

void				ft_usage(void);
void				ft_malloc_error(t_env *e);
void				exit_message(char *str);

/*
** PARSER
*/

int					ft_htod(char c);
int					ft_htoi(char *str);
int					ft_iscolor(char *str);
int					ft_isnumber(char *str);
int					check_value(char **str);
int					name_type(char *str);
void				error_messages(int error);
t_obj				*attribute_object(char **tab_values);
char				*tabtospace(char *str);
void				attribute_scene(int fd, t_env *e);
void				get_scene(char **argv, t_env *e);

#endif
