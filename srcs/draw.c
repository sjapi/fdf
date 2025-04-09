/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/09 19:09:25 by azolotar         ###   ########.fr       */
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
void	draw_line(t_img *img, t_point p1, t_point p2)
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
	img_put_pixel(img, (int)(line.x + 0.5), (int)(line.y + 0.5), 0x00ff00);
	while (i < line.steps)
	{
		line.x += line.x_inc;
		line.y += line.y_inc;
		img_put_pixel(img, (int)(line.x + 0.5), (int)(line.y + 0.5), 0x00ff00);
		i++;
	}
}

void	draw_matrix(t_img *img, t_landscape *l)
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
