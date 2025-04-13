/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/13 19:10:23 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include "mlx.h"

void	re_draw(t_fdf *fdf)
{
	draw_background(fdf);
	draw_matrix(fdf);
	draw_logo(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
}

int	handle_key_hooks(int key, void *param)
{
	printf("%d\n", key);
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->zoom += key == ZOOM_IN;
	fdf->zoom -= key == ZOOM_OUT;
	fdf->origin_x -= (key == LEFT) * 10;
	fdf->origin_x += (key == RIGHT) * 10;
	fdf->origin_y -= (key == UP) * 10;
	fdf->origin_y += (key == DOWN) * 10;
	fdf->angle_x -= (key == ROTATE_LEFT) * 5.0f;
	fdf->angle_x += (key == ROTATE_RIGHT) * 5.0f;
	return (re_draw(fdf), 0);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->angle_x = 30.0f;
	fdf->angle_y = 30.0f;
	fdf->angle_z = 45.0f;
	fdf->zoom = 1;
	fdf->origin_x = 300;
	fdf->origin_y = 300;
}

int	main(int argc, char **argv)
{
	// hello
	t_fdf		fdf;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	if (!ft_is_valid_ext(argv[1], ".fdf"))
		return (ft_putstr("ERROR: Wrong file extension\n"), 1);
	init_fdf(&fdf);
	fdf.l = init_landscape(argv[1]);
	if (!fdf.l)
		return (ft_putstr("ERROR: landscape initialization\n"), 1);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_len, &fdf.endian);
	re_draw(&fdf);
	mlx_key_hook(fdf.win, handle_key_hooks, &fdf);
	mlx_loop(fdf.mlx);
	mlx_destroy_display(fdf.mlx);
	free_landscape(fdf.l, fdf.l->y_len);
	//free(mlx);
	return (0);
}
