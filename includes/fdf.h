/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:40:20 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/17 18:50:12 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define TILE 20

# define ZOOM_IN 61
# define ZOOM_OUT 45

# define ESC 65307
# define UP 107
# define DOWN 106
# define LEFT 104
# define RIGHT 108
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define RESET 114
# define Z_PLUS 109
# define Z_MINUS 110

typedef struct s_dda_line
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}	t_dda_line;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_map_point
{
	int	value;
	int	color;
}	t_map_point;
typedef struct s_map
{
	t_map_point	**mtrx;
	int			x_len;
	int			y_len;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	t_point	origin;
	int		zoom;
	float	z;

	int		origin_x;
	int		origin_y;

	t_map	*m;

	float	angle_x;
	float	angle_y;
	float	angle_z;
}	t_fdf;

/* file */
char		*get_file_content(char *path);

/* map */
t_map		*init_map(char *path);

void		free_map(t_map *m, int i);

/* draw */
void		draw_rect(t_fdf *fdf, t_point p1, t_point p2, int color);

void		print_menu(t_fdf *fdf);

int			draw_iso_map(t_fdf *fdf);

void		draw_42_logo(t_fdf *fdf);

int			get_gradient_color(int color_start, int color_end, float rel_pos);

/* utils */
int			ft_is_valid_ext(char *path, char *ext);

int			ft_atoi_base(char *str, char *base);

int			ft_contains(char *str, char c);

int			ft_split_count(char **split);

int			ft_abs(int n);

int			ft_min(int a, int b);

void		ft_free_split(char **split);

#endif
