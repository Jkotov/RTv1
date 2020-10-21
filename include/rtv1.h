/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:58:47 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 11:30:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <unistd.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include "colors.h"
# include "ini_parser.h"
# include "../libft/include/libft.h"
# define WIDTH 640
# define HEIGHT 480

typedef struct			s_matrix33
{
	float				m[3][3];
}						t_matrix33;

typedef struct			s_surface_coeffs
{
	float				a;
	float				b;
	float				c;
	float				d;
	float				f2;
	float				g2;
	float				h2;
	float				p2;
	float				q2;
	float				r2;
}						t_surface_coeffs;

typedef struct			s_menu
{
	SDL_Rect			menu_size;
	SDL_Texture			*img;
}						t_menu;

typedef struct			s_dot
{
	float				x;
	float				y;
	float				z;
}						t_dot;

typedef struct			s_gui_cache
{
	int					color;
	float				radius;
	float				p_counter;
	t_dot				position;
}						t_gui_cache;

typedef struct			s_camera
{
	t_dot				center_vec;
	t_dot				camera;
	t_dot				*dir_vecs;
	t_dot				angle;
	t_dot				x_vec;
	t_dot				y_vec;
	t_dot				screen_center;
}						t_camera;

typedef struct			s_surface_cache
{
	t_surface_coeffs	c;
	t_dot				angle;
	t_dot				shift;
}						t_surface_cache;

typedef struct			s_surface
{
	t_dot				shift;
	t_surface_coeffs	c;
	int					color;
	int					specular;
	float				reflective;
	t_dot				angle;
	t_surface_cache		cache;
	int					number;
	struct s_surface	*next;
}						t_surface;

typedef struct			s_compute_light_p
{
	t_dot				dot;
	int					specular;
	t_dot				direction_vec;
	t_dot				normal_vec;
}						t_compute_light_p;

/*
** first light is ambient light. Center for it is useless
*/

typedef struct			s_light
{
	t_dot				center;
	float				base_intensity;
	float				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_scene
{
	t_camera			camera;
	t_surface			*shape;
	t_light				*light;
	uint				max_depth;
	uint				cur_depth;
}						t_scene;

typedef struct			s_sdl
{
	int					width;
	int					height;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*fg;
	int					*buffer;
	int					buffer_len;
	int					counter;
	t_scene				scene;
	t_menu				menu;
	char				*scene_file;
}						t_sdl;

void					camera_move(t_sdl *sdl);
void					set_default_scene(t_sdl *sdl);
void					parsing(t_sdl* sdl, char *scene_file);
void					camera_move(t_sdl *sdl);
t_dot					rotate_vector(t_dot v, t_dot angle);
t_dot					cross_product(t_dot v1, t_dot v2);
void					*ft_memset(void *src, int c, size_t len);
t_dot					surface_normal(t_surface_coeffs c, t_dot dot);
t_surface_coeffs		surface_shift(t_surface *s);
t_surface_coeffs		rotate_surface(t_surface *s);
void					matrix_using(t_surface_coeffs c, float m[3][3],\
t_surface_coeffs *res);
void					sphere_cache_calc(t_surface *sphere, t_dot start);
char					dot_cmp(t_dot d1, t_dot d2);
void					directions_vec_compute(t_sdl *sdl, t_dot **dir_vecs);
size_t					ft_strlen(const char *str);
SDL_Texture				*create_texture(char *file_name, t_sdl *sdl);
void					sdl_error(char *text);
void					light_balancer(t_scene *scene);
void					add_light(t_scene *scene, t_dot center,\
float intensity);
void					add_shape(t_surface **list, t_surface surface);
void					scene_init(t_sdl *sdl);
void					init_menu(t_sdl *sdl);
t_sdl					sdl_init(void);
void					clean_light(t_light *light);
void					clean_sphere(t_surface *sphere);
void					clean_scene(t_scene *scene);
void					cleanup(t_sdl *sdl);
void					keyboard_events(t_sdl *sdl, char *quit,\
SDL_Event e, t_surface *cur);
t_surface				*mouse_events(t_sdl *sdl, SDL_Event e,\
t_gui_cache *gui_cache, t_surface *cur);
int						quadratic_equation(t_dot coeffs, float *x1,\
float *x2);
t_dot					vector_sub(t_dot v1, t_dot v2);
t_dot					vector_sum(t_dot v1, t_dot v2);
t_dot					vector_mult_num(t_dot v, float num);
float					scalar_mult(t_dot vec1, t_dot vec2);
float					abs_vector(t_dot vec);
float					q_rsqrt(float number);
float					revers_abs_vec(t_dot vec);
t_dot					vector_normalize(t_dot vector);
float					distance_to_shape(t_surface_coeffs s,\
t_dot v, t_dot start);
t_surface				*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len);
float					specular(t_compute_light_p p,\
t_dot light_vector, float intensity);
float					lighting(t_scene scene, t_compute_light_p p);
int						color_intens(int color, float intens);
int						ray_tracing(t_scene scene, t_dot direction_vector,\
t_dot start);
t_dot					vector_reflection(t_dot direction_vec,\
t_dot normal_vec);
void					render(t_sdl *sdl);
void					loop(t_sdl *sdl);
void					gui_buttons(t_gui_cache *gui_cache, SDL_Event e,\
t_sdl *sdl);
void					del_objs(t_surface **list);
int						count_objs(t_surface *list);
void					button_create_sphere(t_sdl *sdl,\
t_gui_cache *gui_cache);
void					button_create_cone(t_sdl *sdl, t_gui_cache *gui_cache);
void					button_create_plane(t_sdl *sdl, t_gui_cache *gui_cache);
void					button_create_cylinder(t_sdl *sdl,\
t_gui_cache *gui_cache);
void					give_number(t_surface **list);
t_surface				*select_last(t_surface **list, int nb);
//void					gui_light(t_sdl *sdl, SDL_Event e, t_gui_cache *gui_cache);

#endif
