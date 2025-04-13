/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/13 19:23:48 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>

void	img_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	pixel = fdf->addr + (fdf->line_len * y + x * (fdf->bpp / 8));
	*(int *)pixel = color;
}

void	img_put_pixel_safe(t_fdf *fdf, int x, int y, int color)
{
	if (x < 0 || x >= WINDOW_WIDTH)
		return ;
	if (y < 0 || y >= WINDOW_HEIGHT)
		return ;
	img_put_pixel(fdf, x, y, color);
}

/* DDA Algorithm */
void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int			i;
	t_dda_line	line;

	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	if (ft_abs(line.dx) > ft_abs(line.dy))
		line.steps = ft_abs(line.dx);
	else
		line.steps = ft_abs(line.dy);
	line.x_inc = line.dx / line.steps;
	line.y_inc = line.dy / line.steps;
	line.x = p1.x;
	line.y = p1.y;
	i = 0;
	img_put_pixel_safe(fdf, (int)(line.x + 0.5), (int)(line.y + 0.5), color);
	while (i < line.steps)
	{
		line.x += line.x_inc;
		line.y += line.y_inc;
		img_put_pixel_safe(fdf, (int)(line.x + 0.5), (int)(line.y + 0.5), color);
		i++;
	}
}

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		j = -1;	
		while (++j < WINDOW_HEIGHT)
		{
			img_put_pixel_safe(fdf, i, j, 0x000000);
		}
	}
}

int	draw_matrix(t_fdf *fdf)
{
	int		i;
	int		j;
	int		tile_width;
	t_point	current;
	t_point	next;

	tile_width = 20;
	tile_width += fdf->zoom;
	i = -1;
	while (++i < fdf->l->y_len)
	{
		j = -1;
		while (++j < fdf->l->x_len)
		{
			current.x = fdf->origin_x + (j - i) * tile_width;
			current.y = fdf->origin_y + (j + i) * (tile_width / 2) - fdf->l->mtrx[i][j] * tile_width;
			img_put_pixel_safe(fdf, current.x, current.y, 0xffffff);
			if (j < fdf->l->x_len - 1)
			{
				next.x = fdf->origin_x + (j + 1 - i) * tile_width;
				next.y = fdf->origin_y + (j + 1 + i) * (tile_width / 2) - fdf->l->mtrx[i][j + 1] * tile_width;
				draw_line(fdf, current, next, 0xffffff);
			}
			if (i < fdf->l->y_len - 1)
			{
				next.x = fdf->origin_x + (j - i - 1) * tile_width;
				next.y = fdf->origin_y + (j + i + 1) * (tile_width / 2) - fdf->l->mtrx[i + 1][j] * tile_width;
				draw_line(fdf, current, next, 0xffffff);
			}
		}
	}
	return (0);
}

t_point	crp(int x, int y)
{
	t_point	p;

	p.x = 30 + x * 10;
	p.y = 20 + y * 10;
	return (p);
}

void	draw_logo(t_fdf *fdf)
{
	draw_line(fdf, crp(2, 0), crp(3, 0), 0xffffff);
	draw_line(fdf, crp(3, 0), crp(1, 2), 0xffffff);
	draw_line(fdf, crp(1, 2), crp(3, 2), 0xffffff);
	draw_line(fdf, crp(3, 2), crp(3, 4), 0xffffff);
	draw_line(fdf, crp(3, 4), crp(2, 4), 0xffffff);
	draw_line(fdf, crp(2, 4), crp(2, 3), 0xffffff);
	draw_line(fdf, crp(2, 3), crp(0, 3), 0xffffff);
	draw_line(fdf, crp(0, 3), crp(0, 2), 0xffffff);
	draw_line(fdf, crp(0, 2), crp(2, 0), 0xffffff);
	draw_line(fdf, crp(4, 0), crp(5, 0), 0xffffff);
	draw_line(fdf, crp(5, 0), crp(4, 1), 0xffffff);
	draw_line(fdf, crp(4, 1), crp(4, 0), 0xffffff);
	draw_line(fdf, crp(5, 0), crp(6, 0), 0xffffff);
	draw_line(fdf, crp(6, 0), crp(6, 1), 0xffffff);
	draw_line(fdf, crp(6, 1), crp(5, 2), 0xffffff);
	draw_line(fdf, crp(5, 2), crp(5, 3), 0xffffff);
	draw_line(fdf, crp(5, 3), crp(4, 3), 0xffffff);
	draw_line(fdf, crp(4, 3), crp(4, 2), 0xffffff);
	draw_line(fdf, crp(4, 2), crp(5, 1), 0xffffff);
	draw_line(fdf, crp(5, 1), crp(5, 0), 0xffffff);
	draw_line(fdf, crp(6, 2), crp(6, 3), 0xffffff);
	draw_line(fdf, crp(6, 3), crp(5, 3), 0xffffff);
	draw_line(fdf, crp(5, 3), crp(6, 2), 0xffffff);
}

void	draw_menu(t_fdf *fdf)
{
	t_point	origin;

	origin.x = 20;
	origin.y = 60;
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move up:    [k]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move down:  [j]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move left:  [h]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move right: [l]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00, "Zoom in:    [=]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Zoom out:   [-]");
}
