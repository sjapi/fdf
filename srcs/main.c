/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/09 17:34:59 by azolotar         ###   ########.fr       */
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
	printf("key %d tapped\n", key);
	(void)param;
	return (0);
}

int	main(int argc, char **argv)
{
	t_landscape	*landscape;
	void		*mlx;
	void		*win;
	t_img		img;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	landscape = init_landscape(argv[1]);
	if (!landscape)
		return (ft_putstr("ERROR: landscape initialization\n"), 1);
	debug_print(landscape);

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF by azolotar");
	img.mlx_img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img,
			&img.bpp, &img.line_len, &img.endian);
	draw_matrix(&img, landscape);
	mlx_put_image_to_window(mlx, win, img.mlx_img, 0, 0);
	mlx_key_hook(win, handle_input, 0);

	mlx_loop(mlx);

	mlx_destroy_display(mlx);
	//free_landscape(landscape, landscape->y_len);
	//free(mlx);
	return (0);
}
