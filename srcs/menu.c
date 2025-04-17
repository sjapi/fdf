/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:19 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/17 18:46:01 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	draw_line(t_fdf *fdf, t_point p1, t_point p2);

void	img_put_pixel_safe(t_fdf *fdf, int x, int y, int color);

static t_point	crp(int x, int y)
{
	t_point	p;

	p.x = 30 + x * 10;
	p.y = 20 + y * 10;
	return (p);
}

void	draw_42_logo(t_fdf *fdf)
{
	draw_line(fdf, crp(2, 0), crp(3, 0));
	draw_line(fdf, crp(3, 0), crp(1, 2));
	draw_line(fdf, crp(1, 2), crp(3, 2));
	draw_line(fdf, crp(3, 2), crp(3, 4));
	draw_line(fdf, crp(3, 4), crp(2, 4));
	draw_line(fdf, crp(2, 4), crp(2, 3));
	draw_line(fdf, crp(2, 3), crp(0, 3));
	draw_line(fdf, crp(0, 3), crp(0, 2));
	draw_line(fdf, crp(0, 2), crp(2, 0));
	draw_line(fdf, crp(4, 0), crp(5, 0));
	draw_line(fdf, crp(5, 0), crp(4, 1));
	draw_line(fdf, crp(4, 1), crp(4, 0));
	draw_line(fdf, crp(5, 0), crp(6, 0));
	draw_line(fdf, crp(6, 0), crp(6, 1));
	draw_line(fdf, crp(6, 1), crp(5, 2));
	draw_line(fdf, crp(5, 2), crp(5, 3));
	draw_line(fdf, crp(5, 3), crp(4, 3));
	draw_line(fdf, crp(4, 3), crp(4, 2));
	draw_line(fdf, crp(4, 2), crp(5, 1));
	draw_line(fdf, crp(5, 1), crp(5, 0));
	draw_line(fdf, crp(6, 2), crp(6, 3));
	draw_line(fdf, crp(6, 3), crp(5, 3));
	draw_line(fdf, crp(5, 3), crp(6, 2));
}

void	print_menu(t_fdf *fdf)
{
	t_point	origin;

	origin.x = 20;
	origin.y = 60;
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 25, 0x00bfff,
		"FdF by azolotar");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00,
		"Move up:    [k]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00,
		"Move down:  [j]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00,
		"Move left:  [h]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00,
		"Move right: [l]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00,
		"Zoom in:    [=]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00,
		"Zoom out:   [-]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00,
		"Decrease z: [n]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 20, 0x00ff00,
		"Increase z: [m]");
	mlx_string_put(fdf->mlx, fdf->win, origin.x, origin.y += 40, 0x00ff00,
		"Reset:      [r]");
}
