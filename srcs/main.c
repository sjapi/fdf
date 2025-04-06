/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/04 20:47:56 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

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

int	main(int argc, char **argv)
{
	t_landscape	*landscape;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	landscape = init_landscape(argv[1]);
	if (!landscape)
		return (ft_putstr("ERROR: landscape initialization\n"), 1);
	debug_print(landscape);
	free_landscape(landscape, landscape->y_len);
	return (0);
}
