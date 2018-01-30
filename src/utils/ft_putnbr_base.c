/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <pbie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/30 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int					ft_putnbr_base(size_t number, int base)
{
	const char		*alphanum = "0123456789ABCDEF";
	unsigned int	counter;
	size_t			tmp;

	counter = 0;
	tmp = base;
	while (number / tmp >= (size_t)base)
		tmp *= base;
	while (tmp)
	{
		write(1, &alphanum[number / tmp], 1);
		number %= tmp;
		tmp /= base;
		counter++;
	}
	return (counter);
}