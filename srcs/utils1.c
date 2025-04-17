/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:48:21 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/15 23:08:19 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	ft_is_valid_ext(char *path, char *ext)
{
	int	path_len;
	int	ext_len;

	if (!path || !ext)
		return (0);
	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (path_len < ext_len)
		return (0);
	return (!ft_strncmp(path + path_len - ext_len, ext, ext_len));
}

int	ft_contains(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_split_count(char **split)
{
	int	count;

	count = -1;
	while (split[++count] != 0)
		continue ;
	return (count);
}

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != 0)
		free(split[i]);
	free(split);
}
