/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:01:00 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/09 17:09:14 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <pthread.h>
# include <stdlib.h>
# define WINY 1000
# define WINZ 1000
# define LEG 400
# define FOV 1000
# define TH_NB 50
# define ALPHA_SPEC 100
# define SHADOW_BIAS 0.001
# define AA_S 20
# define CART_S 20
# define PALETTE_SIZE 40
# define D_ZERO 0.000001
# define PERL_S 600
# define MAX_COLOR 16776960
# define SUN_DISTANCE 3725000

enum				e_obj {
	LIGHT,
	EYE,
	SPHERE,
	CYLINDER,
	CONE,
	PLANE,
	DISK,
	PARABOLOID
};

enum				e_texture {
	NO_TEXTURE,
	LINES,
	COLUMNS,
	CHECKERBOARD,
	EARTH,
	NEARTH,
	PERLIN
};

enum				e_filter {
	NO_FILTER,
	CARTOON,
	SEPIA,
	RED,
	GREEN,
	BLUE,
	CYAN,
	STEREOSCOPIC
};

typedef struct		s_vc
{
	double			x;
	double			y;
	double			z;
}					t_vc;

typedef struct		s_ray
{
	t_vc			origin;
	t_vc			direction;
	int				type;
}					t_ray;

typedef struct		s_vclist
{
	t_vc			vector;
	struct s_vclist	*next;
}					t_vclist;

typedef struct		s_file_texture
{
	int				*size;
	int				**tab;
}					t_file_texture;

typedef struct		s_obj
{
	enum e_obj		o_type;
	t_vc			rot;
	t_vc			pos;
	t_vc			phong;
	t_vc			descartes;
	struct s_obj	*cut;
	int				col;
	unsigned int	perturb;
	enum e_texture	texture;
	unsigned int	txt_size;
	t_file_texture	file_txt;
	t_file_texture	file_height;
	double			size;
	t_vc			lm;
	t_vc			rm;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_scene
{
	enum e_filter	filter;
	char			antialias;
	char			blinding_lights;
}					t_scene;

typedef struct		s_hit_rec
{
	double			cost;
	double			t;
	double			t1;
	double			t2;
	double			tr_max;
	char			lit;
	t_vc			n;
	t_vc			s;
	t_vc			v;
	t_vc			lm;
	t_vc			hit_inter;
	t_obj			*hit_obj;
}					t_hit_rec;

typedef struct		s_img
{
	void			*pic;
	char			*info;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*image;
}					t_mlx;

typedef struct		s_env
{
	t_mlx			mlx;
	int				*imgstr;
	int				thread_int;
	int				y;
	int				z;
	t_vclist		*b_lights;
	t_vc			eye_lookfrom;
	t_vc			eye_rot;
	pthread_t		pth[TH_NB];
	pthread_mutex_t	mutex;
	t_obj			*obj_link;
	t_obj			*light_link;
	t_obj			*cut_link;
	t_scene			scene;
	char			eq[51];
	int				nr;
	int				nt;
}					t_env;

/*
** RAYTRACER
*/

int					create_image(t_env *e);
void				draw_point(t_env *e, int x, int y, unsigned int color);
void				*scene_plot(void *arg);
t_ray				create_ray(int y, int z, t_vc eye_rot, t_vc ray_origin);
double				distance_to_inter(t_hit_rec *hit, t_obj *obj_list,
					t_ray ray);
char				nearest_node(t_env *e, t_ray ray, t_hit_rec *hit);
int					is_not_cut(t_obj *obj, t_env *e);
int					compute_point(t_env *e, t_hit_rec *hit, t_ray ray, int a);

/*
** COLOR CALCULATION
*/

int					phong_lighting(t_env *e, t_ray ray, t_hit_rec *hit);
void				perturb_norm(t_hit_rec *hit);
int					specular_diffuse(t_obj *light, t_hit_rec *hit, t_ray ray);

/*
** COLOR FUNCTIONS
*/

int					add_color(int hex1, int hex2);
int					multiply_color(int hex, double mult);
int					color_limits(int col);
int					closest_col(int *palette, int color);
int					major_color(int color);
int					mix_colors(int col1, int col2, double coef);
double				ratio_limits(double i);
t_vc				hextorgb(int hex);

/*
** FILTERS
*/

void				stereoscopic(t_env *e, int color);
int					sepia(int color);
int					apply_filter(t_env *e, int color);

/*
** PARSER
*/

t_obj				*default_sphere(void);
t_obj				*default_cone(void);
t_obj				*default_cylinder(void);
t_obj				*default_cutter(t_obj *obj);
t_obj				*default_plane(void);
t_obj				*default_paraboloid(void);
t_obj				*default_light(void);

char				*skip_whitespace(char *file);
int					ft_htod(char c);
int					ft_htoi(char *str);

char				*objects_items(t_obj *nobj, char *file, enum e_obj obj);
char				*parse_descartes(char *file, t_vc *v);
char				*parse_phong(char *file, t_vc *v);

char				*parse_vc(char *file, t_vc *v);
char				*parse_double(char *file, double *d);
char				*parse_int(char *file, unsigned int *d);
char				*parse_color(char *file, int *col);

char				*parse_sphere(t_env *e, char *file);
char				*parse_cylinder(t_env *e, char *file);
char				*parse_cone(t_env *e, char *file);
char				*parse_plane(t_env *e, char *file);
char				*parse_paraboloid(t_env *e, char *file);

char				*parse_eye(t_env *e, char *file);
char				*parse_light(t_env *e, char *file);
char				*parse_cutter(t_obj *cut, char *file);

enum e_texture		texture_converter(char *str, enum e_obj obj);
enum e_filter		filter_converter(char *str);
char				*parse_texture(char *file, enum e_texture *texture,
					unsigned int *size, enum e_obj obj);
char				*parse_filter(char *file, enum e_filter *filter);

char				*read_scene(int fd, char **av);
char				*parser_error(char *message, char *line);
char				*parse_scene(t_env *e, char *file);
void				create_scene(t_env *e, char *file);
int					parser(t_env *e, int ac, char **av);

/*
** DESCARTES LAWS
*/

int					transparency(t_env *e, int old_color,
					t_ray ray, t_hit_rec *hit);
int					reflection(t_env *e, int old_color,
					t_ray ray, t_hit_rec *hit);

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
t_vc				vec_add(t_vc v1, t_vc v2);
t_vc				vec_sub(t_vc v1, t_vc v2);
t_vc				vec_subp(t_vc *v1, t_vc *v2);
t_vc				vec_croise(t_vc *v1, t_vc *v2);
double				vec_x(t_vc v1, t_vc v2);
double				vec_mod(t_vc v);
t_vc				vec_norm(t_vc v);
t_vc				vec_mult(t_vc v, double x);
double				vec_dot(t_vc v1, t_vc v2);
t_vc				inter_position(t_ray ray, double t);

/*
** SHAPES INTERSECTIONS
*/

double				inter_light(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_sph(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_cone(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_plane(t_ray ray, t_obj *obj);
double				inter_cyl(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				inter_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				quadratic_solver(t_hit_rec *hit, t_vc abc);
char				hit_not_cut(t_hit_rec *hit, t_obj *obj, t_ray ray);
char				hit_cut(t_hit_rec *hit, t_obj *obj, t_ray ray);

/*
** KEYBOARD / MOUSE
*/

void				translation(int key, t_env *e);
void				rotation(int key, t_env *e);
int					deal_key(int key, t_env *e);
int					deal_mouse(int k, int y, int z, t_env *e);

/*
** LIGHTING
*/

t_vc				normal_vectors(t_hit_rec *hit, t_obj *obj, t_ray ray);
double				shadows(t_env *e, t_hit_rec *hit,
					t_obj *light_obj, t_ray ray);

/*
** STRUCTURES INITIALIZATION
*/

t_env				*init_env(void);
int					init_mlx(t_mlx *i_mlx);

/*
** OBJECTS
*/

void				obj_add(t_obj **beg, t_obj *n);
void				clear_list(t_obj *head);

/*
** ERROR MGT
*/

void				ft_usage(void);
void				ft_malloc_error(t_env *e);
void				ft_texture_error(t_env *e);
void				exit_message(char *str);
int					err_malloc_texture(int *size, t_obj *obj);

/*
** FREE STRUCTURES
*/

void				free_split(char **split);
void				free_all_lists(t_env *e);
void				free_color_tab(int **tab, int y);
void				free_size_obj(int *size, t_obj *obj);

/*
** TEXTURES OBJECTS
*/

char				get_lines_cylinder(t_hit_rec *hit, t_ray ray);
char				get_lines_cone(t_hit_rec *hit, t_ray ray);
char				get_lines_sphere(t_hit_rec *hit, t_ray ray);
char				get_columns_sphere(t_hit_rec *hit, t_ray ray);
char				get_checkerboard_sphere(t_hit_rec *hit, t_ray ray);
int					get_texture_sphere(t_hit_rec *hit, t_ray ray);
char				checkerboard_plane(t_hit_rec *hit, t_ray ray);

/*
** TEXTURES FUNCTIONS
*/

char				textures_coef(t_obj *obj, t_hit_rec *hit, t_ray ray);
int					load_texture_to_obj(t_env *e, t_obj *obj);
int					load_tex_height_to_obj(t_env *e, t_obj *obj);
void				replace_char(char *str);

/*
** CARTOONING
*/

int					palette_compare(int *palette, int color);
int					palette_add(int *palette, int color);
char				init_palette(int *palette);
char				create_palette(t_env *e, int *palette);
char				cartooning(t_env *e);

/*
** MISCELLANEOUS
*/

void				create_bmp_file(int *imgstr);
void				antialias(int *imgstr);
int					clr_abs_dif(int col1, int col2);
void				blinding_lights(t_env *e);
void				progression_bar(t_env *e, char *str, int i);

/*
** LEGEND
*/

void				put_pixel(t_env *e, int color, int x, int y);
int					draw_slider_r(t_env *e);
int					draw_cursor_r(t_env *e);
int					draw_slider_g(t_env *e);
int					draw_cursor_g(t_env *e);
int					draw_slider_b(t_env *e);
int					draw_cursor_b(t_env *e);
void				legend(t_env *e);
int					mouse(int x, int y, t_env *e);
int					mouse_press(int button, int x, int y, t_env *e);
int					mouse_release(int button, int x, int y, t_env *e);
int					mykeyhook(int keycode, t_env *e);
int					init_slider(t_env *e);
void				put_in_color(t_env *e);

/*
** BUMP_MAP
*/

t_vc				bump_map(t_ray ray, t_hit_rec *hit);

/*
** PERLIN
*/

float				perlin(float x, float y, float res, unsigned int *perm);
t_file_texture		create_perlin_tex(int res, t_env *e, t_obj *sphere);
int					exit_hook(int k, t_env *e);

#endif
