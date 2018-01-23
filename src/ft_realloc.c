/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/23 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					*ft_realloc(void *p, size_t size)
{
	size_t			s;
	t_block			*b;
	t_block			*new;
	void				*newp;

	if (!p)
		return(ft_malloc(size));
	if (valid_address(p))
	{
		s = align4(size);
		b = get_block(p);
		if (b->size >= s)
			if (b->size - s >= (BLOCK_SIZE + 4))
				split_block(b, s);
		else
		{
			if (b->next && b->next->free
				&& (b->size + BLOCK_SIZE + b->next->size) >= s)
			{
				fusion(b);
				if (b->size - s >= (BLOCK_SIZE + 4))
					split_block(b, s);
			}
			else
			{
				newp = ft_malloc(s);
				if (!newp)
					return (NULL);
				new = get_block(newp);
				copy_block(b, new);
				ft_free(p);
				return (newp);
			}
		}
		return (p);
	}
	return (NULL);
}