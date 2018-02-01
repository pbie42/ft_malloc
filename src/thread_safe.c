/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <pbie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/02/01 14:18:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void			init(void)
{
	int				sz;

	if (!g_mem.init)
	{
		sz = getpagesize() * 13;
		g_mem.sml = new_mem_group(NULL, sz);
		sz = 128 * sz;
		g_mem.med = new_mem_group(NULL, sz);
		g_mem.init = 1;
	}
}

void				*malloc(size_t size)
{
	void			*ptr;

	init();
	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void				free(void *ptr)
{
	init();
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void				*realloc(void *ptr, size_t size)
{
	init();
	if (!(ptr && size))
	{
		if (!ptr)
			return (malloc(size));
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void				*calloc(size_t nitems, size_t size)
{
	char			*ptr;
	int				total_size;
	int				i;

	init();
	total_size = nitems * size;
	if (!(ptr = malloc(total_size)))
		return (NULL);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return ((void *)ptr);
}
