/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:59:27 by azolotar          #+#    #+#             */
/*   Updated: 2025/03/31 19:30:41 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

static int	get_file_size(char *path)
{
	int		fd;
	int		size;
	int		bytes;
	char	buff[512];

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	bytes = read(fd, buff, sizeof(buff));
	while (bytes > 0)
	{
		size += bytes;
		bytes = read(fd, buff, sizeof(buff));
		if (bytes == -1)
			return (close(fd), -1);
	}
	close(fd);
	return (size);
}

char	*get_file_content(char *path)
{
	int		fd;
	int		file_size;
	char	*content;

	file_size = get_file_size(path);
	fd = open(path, O_RDONLY);
	if (file_size == -1 || fd == -1)
		return (NULL);
	content = malloc(sizeof(char) * (file_size + 1));
	if (!content)
		return (close(fd), NULL);
	if (read(fd, content, file_size) == -1)
		return (close(fd), NULL);
	content[file_size] = '\0';
	close(fd);
	return (content);
}
