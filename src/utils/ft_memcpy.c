/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/30 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			i;
	unsigned char		*src_cpy;
	unsigned char		*dst_cpy;

	src_cpy = (unsigned char *)src;
	dst_cpy = (unsigned char *)dest;
	i = -1;
	while (++i < size)
		dst_cpy[i] = src_cpy[i];
	return (dst_cpy);
}