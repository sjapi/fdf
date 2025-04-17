/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/17 20:22:01 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>

void	img_put_pixel_safe(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH)
		return ;
	if (y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = fdf->addr + (fdf->line_len * y + x * (fdf->bpp / 8));
	*(int *)pixel = color;
}

/* DDA Algorithm */
void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int			i;
	float		rel_pos;
	int			color;
	t_dda_line	l;

	l.dx = p2.x - p1.x;
	l.dy = p2.y - p1.y;
	if (ft_abs(l.dx) > ft_abs(l.dy))
		l.steps = ft_abs(l.dx);
	else
		l.steps = ft_abs(l.dy);
	l.x_inc = l.dx / l.steps;
	l.y_inc = l.dy / l.steps;
	l.x = p1.x;
	l.y = p1.y;
	i = 0;
	while (i <= l.steps)
	{
		rel_pos = (float)i / l.steps;
		color = get_gradient_color(p1.color, p2.color, rel_pos);
		img_put_pixel_safe(fdf, (int)(l.x + 0.5), (int)(l.y + 0.5), color);
		l.x += l.x_inc;
		l.y += l.y_inc;
		i++;
	}
}

void	draw_rect(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int	i;
	int	j;

	i = p1.y;
	while (i < p2.y)
	{
		j = p1.x;
		while (j < p2.x)
		{
			img_put_pixel_safe(fdf, j, i, color);
			j++;
		}
		i++;
	}
}

static t_point	get_point(t_fdf *fdf, int x, int y)
{
	int		tile_width;
	int		z;
	t_point	p;

	tile_width = TILE + fdf->zoom;
	p.x = fdf->origin_x + (x - y) * tile_width * 2;
	z = (int)((float)fdf->m->mtrx[y][x].value * fdf->z) *(tile_width);
	p.y = fdf->origin_y + (x + y) * tile_width - z;
	p.color = fdf->m->mtrx[y][x].color;
	return (p);
}

int	draw_iso_map(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point	current;
	t_point	next;

	y = -1;
	while (++y < fdf->m->y_len)
	{
		x = -1;
		while (++x < fdf->m->x_len)
		{
			current = get_point(fdf, x, y);
			if (x < fdf->m->x_len - 1)
			{
				next = get_point(fdf, x + 1, y);
				draw_line(fdf, current, next);
			}
			if (y < fdf->m->y_len - 1)
			{
				next = get_point(fdf, x, y + 1);
				draw_line(fdf, current, next);
			}
		}
	}
	return (0);
}
