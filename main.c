/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:24:51 by azolotar          #+#    #+#             */
/*   Updated: 2025/03/31 20:06:43 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

int	main(int argc, char **argv)
{
	char		*content;
	t_landspace	*landscape;

	if (argc != 2)
		return (ft_putstr("ERROR: Wrong arguments count\n"), 1);
	content = get_file_content(argv[1]);
	if (content == NULL)
		return (ft_putstr("ERROR: Cannot get content from given filename\n"), 1);
	ft_putstr(content);
	free(content);
	return (0);
}
