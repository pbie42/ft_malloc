/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/24 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_mem			glbl_mem = {0, 0, 0, 0};

void					*malloc(size_t size)
{
	t_block			*ptr;
	int				sz;

	if (!glbl_mem.init)
	{
		s = getpagesize() * 13;
		glbl_mem.sml = mem_group(NULL, s);
		s * 128;
		glbl_mem.med = mem_group(NULL, s);
		glbl_mem.init = TRUE;
	}
}