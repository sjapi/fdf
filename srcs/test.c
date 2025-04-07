/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:37:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/07 19:42:25 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

int	handle_input(int key, void *param)
{
	printf("key %d tapped\n", key);
	(void)param;
	return (0);
}

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (img->line_len * y + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw(t_img *img)
{
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		img_put_pixel(img, i, i, 0xff0000);
		img_put_pixel(img, WINDOW_HEIGHT - i, i, 0xff0000);
	}
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF by azolotar");

	img.mlx_img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	draw(&img);
	mlx_put_image_to_window(mlx, win, img.mlx_img, 0, 0);

	mlx_key_hook(win, handle_input, 0);
	mlx_loop(mlx);

	mlx_destroy_display(mlx);
	free(mlx);

	return (0);
}
