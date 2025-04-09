/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/09 21:28:21 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}

/* DDA Algorithm */
void	draw_line(t_img *img, t_point p1, t_point p2, int color)
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
	img_put_pixel(img, (int)(line.x + 0.5), (int)(line.y + 0.5), color);
	while (i < line.steps)
	{
		line.x += line.x_inc;
		line.y += line.y_inc;
		img_put_pixel(img, (int)(line.x + 0.5), (int)(line.y + 0.5), color);
		i++;
	}
}

void	draw_matrix1(t_img *img, t_landscape *l)
{
	int	unit_len;
	int	origin_x;
	int	origin_y;
	int	width;
	int	height;

	width = WINDOW_WIDTH - PADDING * 2;
	height = WINDOW_HEIGHT - PADDING * 2;
	unit_len = 30;//ft_min((width - l->x_len - 1) / l->x_len,
			//(height - l->y_len - 1) / l->y_len);
	width = unit_len * l->x_len + l->x_len + 1;
	height = unit_len * l->y_len + l->y_len + 1;
	origin_y = (WINDOW_HEIGHT - height) / 2;
	while (origin_y < height + (WINDOW_HEIGHT - height) / 2)
	{
		origin_x = (WINDOW_WIDTH - width) / 2;
		while (origin_x < width + (WINDOW_WIDTH - width) / 2)
		{
			img_put_pixel(img, origin_x, origin_y, 0xffffff);
			origin_x += unit_len + 1;
		}
		origin_y += unit_len + 1;
	}
}

void	draw_matrix(t_img *img, t_landscape *l)
{
	int	tile_width = 20;
	int	z = 15;
	t_point origin = (t_point){ 300, 300 };
	for (int i = 0; i < l->y_len; i++)
	{
		for (int j = 0; j < l->x_len; j++)
		{
			printf("%d\n", l->mtrx[i][j]);
			int x = origin.x + (j - i) * tile_width;
			int	y = origin.y + (j + i) * (tile_width / 2) - l->mtrx[i][j] * z;
			img_put_pixel(img, x, y, 0xffffff);
			if (j < l->x_len - 1)
			{
				printf("x\n");
				int next_x = origin.x + (j + 1 - i) * tile_width;
				int next_y = origin.y + (j + 1 + i) * (tile_width / 2) - l->mtrx[i][j + 1] * z;
				draw_line(img, (t_point){x, y}, (t_point){next_x, next_y}, 0xffffff);
			}
			if (i < l->y_len - 1)
			{
				printf("y\n");
				int next_x = origin.x + (j - i - 1) * tile_width;
				int next_y = origin.y + (j + i + 1) * (tile_width / 2) - l->mtrx[i + 1][j] * z;
				draw_line(img, (t_point){x, y}, (t_point){next_x, next_y}, 0xffffff);
			}
			printf("f\n");
		}
	}
}
