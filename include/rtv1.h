/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:58:47 by epainter          #+#    #+#             */
/*   Updated: 2020/09/15 16:57:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <unistd.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <math.h>

typedef struct 			s_menu
{
	SDL_Rect			menu_size;
	SDL_Rect			add_menu_size;
	SDL_Texture			*add_menu;
	SDL_Texture			*img;
}						t_menu;

typedef struct			s_dot
{
	float				x;
	float				y;
	float				z;
}						t_dot;

typedef struct			s_sphere
{
	t_dot				center;
	float				radius;
	int					color;
	int 				specular;
	float				reflective;
	struct s_sphere*	next;
}						t_sphere;

typedef struct			s_compute_light_p
{
	t_dot				dot;
	t_dot				center;
	int					specular;
	t_dot				direction_vec;
	t_dot				normal_vec;
	t_sphere			*cur_sphere;
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
	t_dot				camera;
	float				clipping_plane;
	t_sphere			*sphere;
	t_light				*light;
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
	t_scene				scene;
	t_menu				menu;
}						t_sdl;

size_t 					ft_strlen(const char *str);
void					ft_putstr(const char *s);
SDL_Texture				*create_texture(char *file_name, t_sdl *sdl);
void					sdl_error(char *text);
void					light_balancer(t_scene *scene);
void					add_light(t_scene *scene, t_dot center,\
float intensity);
void					add_sphere(t_sphere **list, t_sphere sphere);
void					scene_init(t_sdl *sdl);
void					init_menu(t_sdl *sdl);
t_sdl					sdl_init(void);
void					clean_light(t_light *light);
void					clean_sphere(t_sphere *sphere);
void					clean_scene(t_scene *scene);
void					cleanup(t_sdl *sdl);
void					keyboard_events(t_sdl *sdl, char *quit, SDL_Event e);
void					mouse_events(t_sdl *sdl, SDL_Event e);
int						quadratic_equation(t_dot coeffs, float *x1,\
float *x2);
t_dot					vector_subtraction(t_dot v1, t_dot v2);
t_dot					vector_sum(t_dot v1, t_dot v2);
t_dot					vector_mult_num(t_dot v, float num);
float					scalar_mult(t_dot vec1, t_dot vec2);
float					abs_vector(t_dot vec);
float					q_rsqrt(float number);
float					revers_abs_vec(t_dot vec);
t_dot					vector_normalize(t_dot vector);
float					distance_to_sphere(t_dot direction_vec,\
t_dot vec_to_center, float radius);
t_sphere				*closest(t_dot start, t_dot direction_vector,\
t_scene scene, float *len);
float					specular(t_compute_light_p p,\
t_dot light_vector, float intensity);
float					lighting(t_scene scene, t_compute_light_p p);
int						color_intens(int color, float intens);
int						ray_tracing(t_scene scene, t_dot direction_vector,\
t_dot start);
void					render(t_sdl *sdl);
void					loop(t_sdl *sdl);

#endif