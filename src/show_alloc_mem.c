/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/30 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void					print_mem_group(char *name, void *addr)
{
	ft_putstr(name);
	ft_putstr(" : 0x");
	ft_putnbr((size_t)addr, 16);
	ft_putstr("\n");
}

void					print_block_info(void *start, void *end, unsigned int size)
{
	ft_putstr("0x");
	ft_putnbr((size_t)start, 16);
	ft_putstr(" - 0x");
	ft_putnbr((size_t)end, 16);
	ft_putstr(" : ");
	ft_putnbr(size, 10);
	ft_putstr(" bytes\n");
}

int					print_mem_block(t_block *mem)
{
	t_block			*block;
	int				size;

	block = mem;
	while (block)
	{
		if (!block->free)
		{
			size += block->size;
			print_block_info(block->ptr, block->ptr + block->size, block->size);
		}
		block = block->next;
	}
	return (size);
}

void					show_alloc_mem(void)
{
	t_mem_g			*mem_g;
	unsigned int	count;

	count = 0;
	mem_g = global_mem.sml;
	while (mem_g)
	{
		print_mem_group("TINY", mem_g->mem);
		count += print_mem_block(mem_g->mem);
		mem_g = mem_g->next;
	}
	mem_g = global_mem.med;
	while (mem_g)
	{
		print_mem_group("SMALL", mem_g->mem);
		count += print_mem_block(mem_g->mem);
		mem_g = mem_g->next;
	}
	mem_g = global_mem.sml;
	if (global_mem.lrg)
	{
		print_mem_group("LARGE", global_mem.lrg);
		count += print_mem_block(global_mem.lrg);
	}
	print_total(count);
}