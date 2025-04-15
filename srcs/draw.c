/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/15 23:38:19 by azolotar         ###   ########.fr       */
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

int	draw_iso_map(t_fdf *fdf)
{
	int		i;
	int		j;
	int		tile_width;
	t_point	current;
	t_point	next;

	tile_width = TILE + fdf->zoom;
	i = -1;
	while (++i < fdf->m->y_len)
	{
		j = -1;
		while (++j < fdf->m->x_len)
		{
			current.x = fdf->origin_x + (j - i) * tile_width * 2;
			current.y = fdf->origin_y + (j + i) * tile_width - fdf->m->mtrx[i][j] * tile_width;
			if (j < fdf->m->x_len - 1)
			{
				next.x = fdf->origin_x + (j + 1 - i) * tile_width * 2;
				next.y = fdf->origin_y + (j + 1 + i) * tile_width - fdf->m->mtrx[i][j + 1] * tile_width;
				draw_line(fdf, current, next, 0xffffff);
			}
			if (i < fdf->m->y_len - 1)
			{
				next.x = fdf->origin_x + (j - i - 1) * tile_width * 2;
				next.y = fdf->origin_y + (j + i + 1) * tile_width - fdf->m->mtrx[i + 1][j] * tile_width;
				draw_line(fdf, current, next, 0xffffff);
			}
		}
	}
	return (0);
}
