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

static t_block			*add_large(t_size size)
{
	t_block				*tmp_block;
	t_block				*new_block;

	new_block = mmap(0, (size + sizeof(t_block)), PROT, ANON, -1, 0);
	new_block->size = size;
	new_block->ptr = (void *)new_block + sizeof(t_block);
	new_block->free = TRUE;
	new_block->next = NULL;
	new_block->prev = NULL;
	if (global_mem.lrg)
	{
		tmp_block = global_mem.lrg;
		while (tmp_block)
			tmp_block = tmp_block->next;
		new_block->prev = tmp_block;
		tmp_block->next = new_block;
	}
	else
		global_mem.lrg = new_block;
	return (new_block);
}

static t_mem_group	*new_mem_group(t_mem_group *current, t_size size)
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

t_block					*new_mem_block(t_block *current, t_size size)
{
	t_block				*new_block;

	if (current->size <= (size + sizeof(t_block)))
		return (current);
	new_block = (void *)((char *)current->ptr + size);
	new_block->size = current->size - (size + sizeof(t_block));
	new_block->ptr = (void *)new_block + sizeof(t_block);
	new_block->free = TRUE;
	new_block->next = current->next;
	current->size = current->size - (new_block->size + sizeof(t_block));
	if (current->next && current->next->next)
		current->next->next->prev = new_block->next;
	current->next = new_block;
	return (current);
}

static t_block			*find_mem(t_size size)
{
	t_mem_group		*tmp_group;
	t_block			*tmp_block;

	if (size < SML)
		tmp_group = global_mem.sml;
	else if (size < MED)
		tmp_group = global_mem.med;
	else
		return (add_large(size));
	while (tmp_group)
	{
		tmp_block = tmp->group->mem;
		while (tmp_block && (tmp_block->size < (size + sizeof(t_block))
			|| tmp_block->free == FALSE))
			tmp_block = tmp_block->next;
		if (tmp_block && tmp_block->size > size)
			return (new_mem_block(tmp_block, size));
		else if (tmp_group->next == NULL)
			new_mem_group(tmp_group, tmp_group->size);
		tmp_group = tmp->group->next;
	}
	return (NULL);
}

void					*ft_malloc(size_t size)
{
	t_block			*ptr;
	int				sz;

	if (!glbl_mem.init)
	{
		sz = getpagesize() * 13; // Page size is 4096 bytes so this is 53248 bytes aka 52kb
		global_mem.sml = new_mem_group(NULL, sz);
		sz * 128; // 6815744 bytes aka 6.5mb
		global_mem.med = new_mem_group(NULL, sz);
		global_mem.init = TRUE;
	}
	ptr = find_mem(size);
	ptr->free = FALSE;
	return (ptr->ptr);
}