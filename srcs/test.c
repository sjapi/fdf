/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:37:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/07 23:28:04 by azolotar         ###   ########.fr       */
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

void	draw_matrix(t_img *img)
{
	int x_len;
	int	y_len;
	int	i;
	int	j;
	int	side_len;

	x_len = 8;
	y_len = 3;
	side_len = (img->line_len - 100 * 2 - (x_len + 1)) / x_len;
	i = 0;
	int y = 100;
	while (i <= y_len)
	{
		j = 0;
		while (j <= x_len)
		{
			int	x = 100 + (j + 1) + side_len * j;
			printf("%d %d\n", x, y);
			img_put_pixel(img, x, y, 0x0000ff);
			j++;
		}
		y += 100;
		i++;
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
	img.addr = mlx_get_data_addr(img.mlx_img,
			&img.bpp, &img.line_len, &img.endian);
	draw_matrix(&img);
	mlx_put_image_to_window(mlx, win, img.mlx_img, 0, 0);
	mlx_key_hook(win, handle_input, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
