/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/16 01:40:20 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include "mlx.h"
#include "libft.h"

int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free_map(fdf->m, fdf->m->y_len);
	free(fdf->mlx);
	exit(0);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->zoom = 0;
	fdf->origin_x = 300;
	fdf->origin_y = 300;
}

void	re_draw(t_fdf *fdf)
{
	draw_background(fdf);
	draw_iso_map(fdf);
	draw_menu_background(fdf);
	draw_42_logo(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
}

int	handle_key_hooks(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == ESC)
		return (close_window(fdf), 0);
	if (key == RESET)
		init_fdf(fdf);
	fdf->zoom += key == ZOOM_IN;
	fdf->zoom -= key == ZOOM_OUT;
	fdf->origin_x -= (key == LEFT) * 10;
	fdf->origin_x += (key == RIGHT) * 10;
	fdf->origin_y -= (key == UP) * 10;
	fdf->origin_y += (key == DOWN) * 10;
	return (re_draw(fdf), 0);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc != 2)
		return (ft_putstr_fd("ERROR: Wrong arguments count\n", 1), 1);
	if (!ft_is_valid_ext(argv[1], ".fdf"))
		return (ft_putstr_fd("ERROR: Wrong file extension\n", 1), 1);
	init_fdf(&fdf);
	fdf.m = init_map(argv[1]);
	if (!fdf.m)
		return (ft_putstr_fd("ERROR: Map initialization failed\n", 1), 1);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_len, &fdf.endian);
	re_draw(&fdf);
	mlx_key_hook(fdf.win, handle_key_hooks, &fdf);
	mlx_hook(fdf.win, 17, 0, close_window, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
