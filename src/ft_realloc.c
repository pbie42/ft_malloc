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

static t_bool		find_lrg(t_block *ptr)
{
	t_block			*tmp;

	tmp = global_mem.lrg;
	while (tmp)
	{
		if (tmp == ptr)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void					extend_block(t_block *tmp, size_t size)
{
	t_block			*new;

	new = (void *)tmp + size;
	new->size = (tmp->size + tmp->next->size) - size;
	tmp->free = FALSE;
	tmp->size = size;
	tmp->next->prev = new;
	if (tmp->next->next)
		tmp->next->next->prev = new;
	new->next = tmp->next->next;
	tmp->next = new;
	new->prev = tmp;
	new->free = TRUE;
	new->ptr = (void *)new + sizeof(t_block);
}

void					*ft_realloc(void *ptr, size_t size)
{
	t_block			*tmp;
	t_block			*new;

	tmp = ptr - sizeof(t_block);
	if (!find_mem(tmp, global_mem.sml, NULL)
		|| !find_mem(tmp, global_mem.med, NULL) || !find_lrg(tmp))
		return (NULL);
	if (tmp->size > size + sizeof(t_block))
	{
		new = new_mem_block(tmp, size);
		fusion(tmp->next, NULL);
	}
	else if (tmp->size < size + sizeof(t_block) && tmp->next
				&& tmp->next->free && tmp->next->size + tmp->size > size)
	{
		extend_block(tmp, size);
		return (tmp->ptr);
	}
	else
	{
		new = ft_malloc(size);
		ft_memcpy(new, tmp->ptr, size < tmp->size ? size : tmp->size);
		ft_free(ptr);
	}
	return (new);
}