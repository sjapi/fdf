/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/12 20:58:43 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include "mlx.h"

void	debug_print(t_landscape *l)
{
int	i;
	int	j;

	printf("x: %d\n", l->x_len);
	printf("y: %d\n", l->y_len);
	i = 0;
	while (i < l->y_len)
	{
		j = 0;
		while (j < l->x_len)
		{
			printf("%5d ", l->mtrx[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	handle_input(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	printf("key: %d\n", key);
	if (key == ZOOM_IN)
		fdf->zoom++;
	else if (key == ZOOM_OUT)
		fdf->zoom--;
	else if (key == LEFT)
		fdf->origin_x -= 4;
	else if (key == RIGHT)
		fdf->origin_x += 4;
	else if (key == UP)
		fdf->origin_y -= 4;
	else if (key == DOWN)
		fdf->origin_y += 4;
	draw_matrix(fdf);
	(void)param;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
//	t_landscape	*landscape;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	fdf.l = init_landscape(argv[1]);
	if (!fdf.l)
		return (ft_putstr("ERROR: landscape initialization\n"), 1);
	debug_print(fdf.l);

	fdf.mlx = mlx_init();

	fdf.win = mlx_new_window(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF by azolotar");

	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_len, &fdf.endian);
	draw_matrix(&fdf);

	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	fdf.zoom = 1;
	fdf.origin_x = 300;
	fdf.origin_y = 300;
	mlx_key_hook(fdf.win, handle_input, &fdf);
//	mlx_loop_hook(fdf.mlx, draw_matrix, &fdf);
	mlx_loop(fdf.mlx);

	mlx_destroy_display(fdf.mlx);
	//free_landscape(landscape, landscape->y_len);
	//free(mlx);
	return (0);
}
