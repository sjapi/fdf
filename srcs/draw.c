/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/13 16:03:29 by azolotar         ###   ########.fr       */
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
	int		tile_width;
	t_point	current;
	t_point	next;

	tile_width = 20;
	tile_width += fdf->zoom;
	printf("tile width %d\n", tile_width);
	for (int i = 0; i < fdf->l->y_len; i++)
	{
		for (int j = 0; j < fdf->l->x_len; j++)
		{
			current.x = fdf->origin_x + (j - i) * tile_width;
			current.y = fdf->origin_y + (j + i) * (tile_width / 2) - fdf->l->mtrx[i][j] * Z_MULTIPLIER;
			img_put_pixel_safe(fdf, current.x, current.y, 0xffffff);
			if (j < fdf->l->x_len - 1)
			{
				next.x = fdf->origin_x + (j + 1 - i) * tile_width;
				next.y = fdf->origin_y + (j + 1 + i) * (tile_width / 2) - fdf->l->mtrx[i][j + 1] * Z_MULTIPLIER;
				draw_line(fdf, current, next, 0xffffff);
			}
			if (i < fdf->l->y_len - 1)
			{
				next.x = fdf->origin_x + (j - i - 1) * tile_width;
				next.y = fdf->origin_y + (j + i + 1) * (tile_width / 2) - fdf->l->mtrx[i + 1][j] * Z_MULTIPLIER;
				draw_line(fdf, current, next, 0xffffff);
			}
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
	return (0);
}

void	draw_menu(t_fdf *fdf)
{
	t_point	origin;

	origin.x = 20;
	origin.y = 0;
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move up:    [k]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move down:  [j]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move left:  [h]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Move right: [l]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00, "Zoom in:    [=]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00, "Zoom out:   [-]");
}
