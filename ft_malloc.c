/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2016/12/11 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_session			*session = NULL;
void					*base = NULL;

t_block				*find_block(t_block *last, size_t size)
{
	t_block			*b;

	b = base;
	while (b && !(b->free && b->size >= size))
	{
		last = b;
		b = b->next;
	}
	return (b);
}

t_block				*extend_heap(t_block *last, size_t s)
{
	t_block			*b;

	b = sbrk(0);
	if (sbrk(BLOCK_SIZE + s) == (void *)-1)
		return (NULL);
	b->size = s;
	b->next = NULL;
	if (last)
		last->next = b;
	b->free = FALSE;
	return (b);
}

void					split_block(t_block *b, size_t s)
{
	t_block			*new;

	new = b->data + s;
	new->size = b->size - s - BLOCK_SIZE;
	new->next = b->next;
	new->free = TRUE;
	b->size = s;
	b->next = new;
}

void					*ft_malloc(size_t size)
{
	t_block			*b;
	t_block			*last;
	size_t			s;

	if (size <= 0)
		return (NULL);
	s = align4(size);
	if (base)
	{
		// first find a block
		last = base;
		b = find_block(last, s);
		if (b)
		{
			// Can we split?
			if ((b->size - s) >= (BLOCK_SIZE + 4))
				split_block(b, s);
			b->free = FALSE;
		}
		else
		{
			// No fitting block, extend the heap
			b = extend_heap(last, s);
			if (!b)
				return (NULL);
		}
	}
	else
	{
		// first time
		b = extend_heap(NULL, s);
		if (!b)
			return (NULL);
		base = b;
	}
	return (b->data);
}