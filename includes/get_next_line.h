/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:49:31 by azolotarev        #+#    #+#             */
/*   Updated: 2025/04/09 17:26:30 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

int		ft_str_contains(char *str, char c);

int		ft_strlen_till(char *str, char c);

#endif
