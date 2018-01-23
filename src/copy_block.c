/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/23 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					copy_block(t_block *src, t_block *dest)
{
	int				*sdata;
	int				*ddata;
	size_t			i;

	sdata = src->ptr;
	ddata = dest->ptr;
	i = -1;
	while ((++i * 4) < src->size && (i * 4) < dest->size)
		ddata[i] = sdata[i];
}