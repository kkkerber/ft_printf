/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vakhapil <vakhapil@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by vakhapil          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by vakhapil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count = ft_print_unsigned(n / 10);
		if (count < 0)
			return (-1);
	}
	if (ft_print_char('0' + n % 10) < 0)
		return (-1);
	return (count + 1);
}

static int	ft_print_long(long n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count = ft_print_long(n / 10);
		if (count < 0)
			return (-1);
	}
	if (ft_print_char('0' + n % 10) < 0)
		return (-1);
	return (count + 1);
}

int	ft_print_signed(int n)
{
	long	nb;
	int		count;

	nb = n;
	if (nb < 0)
	{
		if (ft_print_char('-') < 0)
			return (-1);
		nb = -nb;
		count = ft_print_long(nb);
		if (count < 0)
			return (-1);
		return (count + 1);
	}
	return (ft_print_long(nb));
}

int	ft_print_hex(unsigned long n, const char *digits)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count = ft_print_hex(n / 16, digits);
		if (count < 0)
			return (-1);
	}
	if (ft_print_char(digits[n % 16]) < 0)
		return (-1);
	return (count + 1);
}
