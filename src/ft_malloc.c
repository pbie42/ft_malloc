/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/24 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_mem			global_mem = {0, 0, 0, 0};

static void			*new_mem_group(t_mem_group *current, t_size size)
{
	t_mem_group		*mem_group;
	t_block			*tmp_block;

	mem_group = mmap(0, size, PROT, ANON, -1, 0);
	mem_group->size = size - sizeof(t_mem_group);
	mem_group->mem = (void *)mem_group + sizeof(t_mem_group);
	mem_group->next = NULL;
	tmp_block = mem_group->mem;
	tmp_block->size = mem_group->size - sizeof(t_block);
	tmp_block->ptr = (void *)tmp_block + sizeof(t_block);
	tmp_block->free = TRUE;
	tmp_block->next = NULL;
	tmp_block->prev = NULL;
	if (current)
		current->next = mem_group;
	return (mem_group);
}

void					*ft_malloc(size_t size)
{
	t_block			*ptr;
	int				sz;

	if (!glbl_mem.init)
	{
		s = getpagesize() * 13; // Page size is 4096 bytes so this is 53248 bytes aka 52kb
		global_mem.sml = new_mem_group(NULL, s);
		s * 128; // 6815744 bytes aka 6.5mb
		global_mem.med = new_mem_group(NULL, s);
		global_mem.init = TRUE;
	}
}