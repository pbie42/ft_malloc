/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2016/12/11 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					*ft_calloc(size_t number, size_t size)
{
	size_t			*new;
	size_t			s4;
	size_t			i;

	i = -1;
	new = ft_malloc(number * size);
	if (new)
	{
		s4 = align4(number * size) << 2;
		while (++i < s4)
			new[i] = 0;
	}
	return (new);
}