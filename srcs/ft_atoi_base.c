/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:27:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/14 20:27:51 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	power(int base, int exp)
{
	int	result;

	result = 1;
	while (exp)
	{
		result *= base;
		exp--;
	}
	return (result);
}

static int	is_valid_base(char *base, int base_len)
{
	int	i;
	int	j;

	if (base_len < 2)
		return (0);
	i = 0;
	while (i < base_len)
	{
		j = i + 1;
		while (j < base_len)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	while (*base)
	{
		if (*base == '+' || *base == '-' || *base == ' ' || *base == '\n'
			|| *base == '\t' || *base == '\v' || *base == '\f' || *base == '\r')
			return (0);
		base++;
	}
	return (1);
}

static int	get_decimal_value(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	atoi(char *str, char *base, int base_len)
{
	int	num_len;
	int	result;

	num_len = 0;
	while (get_decimal_value(base, *str) != -1)
	{
		num_len++;
		str++;
	}
	str -= num_len;
	result = 0;
	while (num_len > 0)
	{
		result += power(base_len, num_len - 1) * get_decimal_value(base, *str);
		num_len--;
		str++;
	}
	return (result);
}

int	ft_atoi_base(char *str, char *base)
{
	int	base_len;
	int	minus_count;
	int	result;

	base_len = 0;
	while (base[base_len])
		base_len++;
	minus_count = 0;
	if (!is_valid_base(base, base_len))
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_count++;
		str++;
	}
	result = atoi(str, base, base_len);
	if (minus_count % 2 == 1)
		result *= -1;
	return (result);
}
