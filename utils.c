/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:48:21 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/01 18:57:42 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		str += write(1, str, 1);
}

int	ft_atoi(char *str)
{
	int	negative;
	int	result;

	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	negative = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	result = 0;
	while (*str <= '0' && *str >= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (negative)
		result *= -1;
	return (result);
}
