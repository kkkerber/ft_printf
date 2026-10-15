/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vakhapil <vakhapil@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by vakhapil          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by vakhapil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *pointer)
{
	int	count;

	if (!pointer)
		return (ft_print_string("(nil)"));
	if (ft_print_string("0x") < 0)
		return (-1);
	count = ft_print_hex((unsigned long)pointer, "0123456789abcdef");
	if (count < 0)
		return (-1);
	return (count + 2);
}
