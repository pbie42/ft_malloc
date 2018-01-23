/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/23 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					ft_free(void *p)
{
	t_block			*b;
	if (valid_address(p))
	{
		b = get_block(p);
		b->free = TRUE;
		if (b->prev && b->prev->free)
			b = fusion(b->prev);
		if (b->next)
			fusion(b);
		else
		{
			if (b->prev)
				b->prev->next = NULL;
			else
				set_base(NULL);
			brk(b);
		}
	}
}