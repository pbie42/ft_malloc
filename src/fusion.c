/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/23 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block				fusion(t_block *b)
{
	if (b->next && b->next->free)
	{
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
	}
	return (b);
}