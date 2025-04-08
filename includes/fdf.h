/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:38:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/07 18:37:14 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define PADDING 100

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

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

void		ft_putstr(char *str);

int			ft_abs(int n);

int			ft_min(int x, int y);

int			ft_max(int x, int y);

char		*get_file_content(char *path);

t_landscape	*init_landscape(char *str);

void		free_landscape(t_landscape *l, int i);

#endif
