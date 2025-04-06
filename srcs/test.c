/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:37:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/06 21:40:16 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

int	main(void)
{
	void			*mlx;
	void			*mlx_window;
	t_mlx_data_addr	image;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Sueta");
	image.image = mlx_new_image(mlx, 800, 800);
	image.data_addr = mlx_get_data_addr(image.image, &image.bits_per_pixel, &image.size_line, &image.endian);
	mlx_loop(mlx);
	ft_putstr_fd("hello world", 1);
}
