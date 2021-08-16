/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:08:35 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 19:08:37 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./minilibx_mms/mlx.h"
# include "./libft_rt/libft.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>

# define PI 3.14159265359
# define EPSILON 0.000001
# define ESC 53
# define KEYPRESS 2
# define CHANGECAMERA 8
# define DESTROYNOTIFY 17

# pragma pack(push, 1)

typedef struct	s_bmp
{
	unsigned char	file_type1;
	unsigned char	file_type2;
	unsigned int	file_size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	int				image_width;
	int				image_height;
	unsigned short	planes;
	unsigned short	bit_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				x_pixel_per_meter;
	int				y_pixel_per_meter;
	unsigned int	total_color;
	unsigned int	important_color;
}				t_bmp;

# pragma pack(pop)

typedef	struct	s_vector3
{
	double	x;
	double	y;
	double	z;
}				t_vector3;

typedef struct	s_ray
{
	t_vector3	origin;
	t_vector3	direct;
}				t_ray;

typedef	struct	s_all_light
{
	t_vector3	ambient;
	t_vector3	diffuse;
	t_vector3	specular;
	t_vector3	object_rgb;
}				t_all_light;

typedef struct	s_resoltion
{
	int	screen_x;
	int	screen_y;
}				t_resoltion;

typedef struct	s_ambient
{
	double		ratio;
	t_vector3	color;
}				t_ambient;

typedef struct	s_camera
{
	t_vector3	origin;
	t_vector3	direct;
	double		fov;
	double		focal_length;
	double		screen_ratio;
	double		viewport_h;
	double		viewport_w;
	t_vector3	viewport_center;
	t_vector3	horizontal;
	t_vector3	vertical;
	t_vector3	lower_left_corner;
}				t_camera;

typedef struct	s_cam_info
{
	t_vector3	origin;
	t_vector3	direct;
	double		fov;
}				t_cam_info;

typedef struct	s_light
{
	t_vector3	origin;
	double		brightness;
	t_vector3	color;
}				t_light;

typedef struct	s_sphere
{
	t_vector3	center;
	double		r;
	t_vector3	color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3	center;
	t_vector3	normal;
	t_vector3	color;
}				t_plane;

typedef struct	s_square
{
	t_vector3	center;
	t_vector3	normal;
	double		size;
	t_vector3	color;
	t_vector3	horizontal;
	t_vector3	vertical;
}				t_square;

typedef struct	s_cylinder
{
	t_vector3	center;
	t_vector3	normal;
	t_vector3	color;
	double		r;
	double		h;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector3	normal;
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_vector3	color;
}				t_triangle;

typedef struct	s_inter
{
	double	solution;
	char	object;
	int		inout;
	int		index;
}				t_inter;

typedef struct	s_hit_light
{
	t_vector3	object_rgb;
	t_vector3	normal;
	double		*n_dot_pl;
	double		*diffuse;
}				t_hit_light;

typedef struct	s_point_ray
{
	t_vector3	point;
	t_vector3	point_to_cam;
	double		*limit_len;
	t_vector3	*point_to_light;
}				t_point_ray;

typedef struct	s_object_inter
{
	int		object_num;
	int		pl_num;
	int		sp_num;
	int		sq_num;
	int		cy_num;
	int		tr_num;
	t_inter	*object;
	t_inter	nothing;
}				t_object_inter;

typedef struct	s_rt
{
	t_resoltion	r;
	t_ambient	a;
	t_list		*c;
	t_list		*l;
	t_list		*sp;
	t_list		*pl;
	t_list		*sq;
	t_list		*cy;
	t_list		*tr;
}				t_rt;

typedef struct	s_data
{
	void		*ptr;
	void		*window;
	void		*image;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_resoltion	max;
	t_vector3	pixel_color;
}				t_data;

typedef struct	s_info
{
	int			c_num;
	int			l_num;
	int			pl_num;
	int			sp_num;
	int			sq_num;
	int			cy_num;
	int			tr_num;
	t_data		*data;
	t_resoltion	r;
	t_ambient	a;
	t_list		*c;
	t_light		*l;
	t_plane		*pl;
	t_sphere	*sp;
	t_square	*sq;
	t_cylinder	*cy;
	t_triangle	*tr;
}				t_info;

typedef struct	s_quadratic
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
}				t_quadratic;

typedef struct	s_tr_sol
{
	t_vector3	p1p2;
	t_vector3	p1p3;
	t_vector3	p2p3;
	t_vector3	p2p1;
	t_vector3	p3p1;
	t_vector3	p3p2;
}				t_tr_sol;

t_vector3		vec3_add(t_vector3 u, t_vector3 v);
t_vector3		vec3_sub(t_vector3 u, t_vector3 v);
t_vector3		vec3_multi(t_vector3 u, t_vector3 v);
t_vector3		vec3_div(t_vector3 u, t_vector3 v);
t_vector3		vec3_scalar(t_vector3 vec, double scala);
double			vec3_dot(t_vector3 u, t_vector3 v);
t_vector3		vec3_cross(t_vector3 u, t_vector3 v);
double			vec3_len(t_vector3 vec);
t_vector3		vec3_unit(t_vector3 vec);
t_vector3		vec3_max_1(t_vector3 u);
t_vector3		vec3_set(double x, double y, double z);
t_ray			ray_create(t_vector3 origin, t_vector3 direct);
t_vector3		ray_hit_point(t_ray ray, double t);
t_ray			cam_to_screen_ray(t_camera cam, double u, double v);
t_vector3		rotate_x(t_vector3 vec, double theta);
t_vector3		rotate_y(t_vector3 vec, double theta);
t_vector3		rotate_z(t_vector3 vec, double theta);
void			free_comma(char **comma);
void			set_start_pointer(char **p1, char **p2);
int				check_set_vec3(t_vector3 *vec, char **comma);
int				check_vec3_in_range(t_vector3 vec, double min, double max);
int				check_set_num(double *num, char *factor);
int				check_r(char **factor, t_rt *rt);
int				check_a(char **factor, t_rt *rt);
int				check_c(char **factor, t_rt *rt);
int				check_l(char **factor, t_rt *rt);
int				check_sp(char **factor, t_rt *rt);
int				check_pl(char **factor, t_rt *rt);
int				check_sq(char **factor, t_rt *rt);
int				check_cy(char **factor, t_rt *rt);
int				check_tr(char **factor, t_rt *rt);
int				check_specifier(char **factor, t_rt *rt);
int				check_line(char *line, t_rt *rt);
int				check_arg_ret_fd(int argc, char **argv);
int				read_file_gnl(int fd, t_rt *rt);
int				check_rt_file(int fd, t_rt *rt);
void			set_ra_count_object_num(t_info *info, t_rt *rt);
void			set_light(t_info *info, t_rt *rt);
t_camera		*camera_create(t_cam_info *c, t_resoltion r);
void			set_camera(t_info *info, t_rt *rt);
void			set_sphere(t_info *info, t_rt *rt);
void			set_plane(t_info *info, t_rt *rt);
void			set_square(t_info *info, t_rt *rt);
void			set_triangle(t_info *info, t_rt *rt);
void			set_cylinder(t_info *info, t_rt *rt);
void			info_init(t_info *info, t_rt *rt, t_data *data);
void			rt_init(t_rt *rt);
t_resoltion		limit_screen(t_resoltion rt_r, t_resoltion max);
void			data_init(t_data *data, t_rt *rt);
t_inter			hit_sphere(t_ray cam_ray, t_sphere sphere, int idx);
t_inter			hit_plane(t_ray cam_ray, t_plane plane, int idx);
t_inter			hit_square(t_ray cam_ray, t_square square, int idx);
t_inter			hit_triangle(t_ray cam_ray, t_triangle triangle, int idx);
t_inter			hit_cylinder(t_ray cam_ray, t_cylinder cylinder, int idx);
void			inter_init(t_inter *inter, char object, int idx);
t_inter			near_object(t_object_inter *object_inter);
void			object_inter_init(t_object_inter *obj_inter, t_info *info);
void			set_object_inter(t_object_inter *obj_inter, t_ray cam_ray,
				t_info *info);
t_object_inter	*hit_object(t_ray cam_ray, t_info *info);
t_point_ray		*ret_point_light(t_ray cam_ray, t_inter inter, t_info *info);
t_inter			*ret_point_shade(t_point_ray *point_ray, t_info *info);
void			*get_sphere_light(t_hit_light *hl, t_point_ray *pr,
				t_inter inter, t_info *info);
void			*get_plane_light(t_hit_light *hl, t_point_ray *pr,
				t_inter inter, t_info *info);
void			*get_square_light(t_hit_light *hl, t_point_ray *pr,
				t_inter inter, t_info *info);
void			*get_cylinder_light(t_hit_light *hl, t_point_ray *pr,
				t_inter inter, t_info *info);
void			*get_triangle_light(t_hit_light *hl, t_point_ray *pr,
				t_inter inter, t_info *info);
t_hit_light		*get_object_light(t_point_ray *point_ray, t_inter inter,
				t_info *info);
t_all_light		light_sum(t_point_ray *point_ray, t_inter *shade,
				t_hit_light *hit_info, t_info *info);
t_vector3		ray_color(t_ray cam_ray, t_inter inter, t_info *info);
int				color_vec3_to_int(t_data *data, t_vector3 pixel_color);
int				get_pixel_color(t_info *info, t_camera *cam,
				double u, double v);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_pixel(t_info *info, t_camera *cam);
void			draw_window_loop(t_info *info, int bmp_fd);
int				key_check(int key, t_info *info);
int				button_check(t_info *info);
void			init_bmp_header(t_bmp *bmp, t_info *info);
void			save_bmp(int bmp_fd, t_info *info);
int				check_save_ret_fd(int argc, char **argv);
int				is_space(char s);
int				word_num(char *s);
int				rt_atoi(char *str, int *move);
double			rt_atof(char **str);
char			**split_space(char *s);
char			**split_comma(char *s);
int				get_next_line(int fd, char **line);

#endif
