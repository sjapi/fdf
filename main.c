/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/01 18:06:54 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	char		*content;
	t_landscape	*landscape;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	content = get_file_content(argv[1]);
	if (content == NULL)
		return (ft_putstr("ERROR: Cannot get content from given filename\n"), 1);
	landscape = create_landscape(content);
	printf("x: %5d\ny: %5d\n", landscape->x_len, landscape->y_len);
	free(content);
	return (0);
}
