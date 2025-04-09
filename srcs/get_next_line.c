/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:50:46 by azolotarev        #+#    #+#             */
/*   Updated: 2025/04/09 17:27:01 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*i_love_norminette(int fd, int *br, char *line, char *buf)
{
	char	*tmp;

	*br = read(fd, buf, BUFFER_SIZE);
	if (*br == -1)
	{
		free(buf);
		return (NULL);
	}
	buf[*br] = '\0';
	tmp = line;
	line = ft_strjoin(line, buf);
	if (!line)
	{
		free(buf);
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (line);
}

static char	*s_fill_buf(int fd, char *line)
{
	int		bytes_read;
	char	*buf;

	if (!line)
	{
		line = malloc(sizeof(char) * 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (line && bytes_read > 0 && !ft_str_contains(line, '\n'))
	{
		line = i_love_norminette(fd, &bytes_read, line, buf);
		if (!line)
			return (NULL);
	}
	free(buf);
	return (line);
}

static char	*s_get_line(char *buf)
{
	char	*res;
	int		len;
	int		i;

	if (!buf[0])
		return (NULL);
	len = ft_strlen_till(buf, '\n');
	if (ft_str_contains(buf, '\n'))
		res = malloc(sizeof(char) * (len + 2));
	else
		res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

static char	*s_get_next_buf(char *buf)
{
	int		line_len;
	int		buf_len;
	int		i;
	char	*res;

	line_len = ft_strlen_till(buf, '\n');
	if (buf[line_len] == '\0')
	{
		free(buf);
		return (NULL);
	}
	buf_len = ft_strlen_till(buf, 0) - line_len - 1;
	res = malloc(sizeof(char) * (buf_len + 1));
	if (!res)
		return (NULL);
	line_len += 1;
	i = 0;
	while (i < buf_len)
		res[i++] = buf[line_len++];
	res[i] = '\0';
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buf != NULL)
		{
			free(buf);
			buf = NULL;
		}
		return (NULL);
	}
	buf = s_fill_buf(fd, buf);
	if (!buf)
		return (NULL);
	line = s_get_line(buf);
	buf = s_get_next_buf(buf);
	return (line);
}
