/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:40:20 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/13 19:28:50 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

# define PADDING 100

# define Z_MULTIPLIER 10

# define ZOOM_IN 61
# define ZOOM_OUT 45

# define UP 107
# define DOWN 106
# define LEFT 104
# define RIGHT 108
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363

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

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_landscape
{
	int	**mtrx;
	int	x_len;
	int	y_len;
}	t_landscape;

typedef struct	s_fdf
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

	int		origin_x;
	int		origin_y;

	t_landscape *l;

	float	angle_x;
	float	angle_y;
	float	angle_z;
	
}	t_fdf;

void		ft_putstr(char *str);

int			ft_abs(int n);

int			ft_min(int x, int y);

int			ft_max(int x, int y);

int			ft_is_valid_ext(char *path, char *ext);

char		*get_file_content(char *path);

t_landscape	*init_landscape(char *str);

void		free_landscape(t_landscape *l, int i);

void		draw_background(t_fdf *fdf);

void		draw_menu(t_fdf *fdf);

int			draw_matrix(t_fdf *fdf);

void		draw_logo(t_fdf *fdf);

#endif
