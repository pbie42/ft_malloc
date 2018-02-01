/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <pbie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/02/01 14:08:21 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_bool		free_lrg(t_block *addr)
{
	t_block			*tmp;
	t_bool			freed;

	tmp = g_mem.lrg;
	freed = FALSE;
	while (tmp && !freed)
	{
		if (tmp == addr)
		{
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp == g_mem.lrg)
				g_mem.lrg = tmp->next;
			munmap(tmp, tmp->size + sizeof(t_block));
			freed = TRUE;
		}
		tmp = tmp->next;
	}
	return (freed);
}

t_mem_g				*find_mem(t_block *ptr, t_mem_g *mem_g, t_mem_g **prev)
{
	t_block			*tmp;

	if (prev)
		*prev = NULL;
	while (mem_g)
	{
		if ((void *)mem_g->mem <= (void *)ptr
			&& (void *)ptr <= (void *)mem_g->mem + mem_g->size)
		{
			tmp = mem_g->mem;
			while (tmp)
			{
				if (tmp == ptr)
					return (mem_g);
				tmp = tmp->next;
			}
			return (NULL);
		}
		if (prev)
			*prev = mem_g;
		mem_g = mem_g->next;
	}
	return (NULL);
}

t_mem_g				*fusion(t_block *ptr, t_mem_g **prev)
{
	t_mem_g			*tmp;

	if (!((tmp = find_mem(ptr, g_mem.sml, prev))
		|| (tmp = find_mem(ptr, g_mem.med, prev))))
		return (NULL);
	ptr->free = TRUE;
	if (ptr->prev && ptr->prev->free)
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size += ptr->size + sizeof(t_block);
		if (ptr->next)
			ptr->next->prev = ptr->prev;
		ptr = ptr->prev;
	}
	if (ptr->next && ptr->next->free)
	{
		ptr->size += ptr->next->size + sizeof(t_block);
		ptr->next = ptr->next->next;
		if (ptr->next)
			ptr->next->prev = ptr;
	}
	return (tmp);
}

void				ft_free(void *ptr)
{
	t_mem_g			*tmp_group;
	t_mem_g			*prv_group;
	t_block			*tmp_block;

	if (!ptr)
		return ;
	tmp_block = ptr - sizeof(t_block);
	if (free_lrg(ptr))
		return ;
	if (!(tmp_group = fusion(tmp_block, &prv_group)))
		return ;
	if (prv_group && !((t_block *)tmp_group->mem)->next)
	{
		prv_group->next = tmp_group->next;
		munmap(tmp_group, tmp_group->size + sizeof(tmp_group));
	}
}
