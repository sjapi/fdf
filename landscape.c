/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:39:55 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/01 18:09:08 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static int	get_x_len(char *str)
{
	int	x_len;

	x_len = 0;
	while (*str && *str == ' ')
	{
		str++;
	}
	while (*str != '\n' && *str != '\0')
	{
		while (*str && (*str == '-' || (*str >= '0' && *str <= '9')))
		{
			str++;
		}
		while (*str && *str == ' ')
		{
			str++;
		}
		x_len += 1;
	}
	return (x_len);
}

static int	get_y_len(char *str)
{
	int	y_len;

	y_len = 0;
	while (*str)
	{
		if (*str == '\n')
		{	
			y_len += 1;
		}
		str++;
	}
	return (y_len);
}

static int	fill_mtrx(t_landscape *landscape, char *str)
{
	(void)landscape;
	(void)str;
	return (0);
}

t_landscape	*create_landscape(char *str)
{
	t_landscape	*landscape;

	landscape = malloc(sizeof(t_landscape));
	if (!landscape)
		return (NULL);
	landscape->x_len = get_x_len(str);
	landscape->y_len = get_y_len(str);
	if (fill_mtrx(landscape, str) == -1)
	{
		// handle error
	}
	return (landscape);
}
