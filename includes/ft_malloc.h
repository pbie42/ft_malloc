/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <pbie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/09/29 15:19:02 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TRUE 1
# define FALSE 0
# define SML 512
# define MED 4096
# define PROT PROT_READ|PROT_WRITE
# define ANON MAP_PRIVATE|MAP_ANONYMOUS

# include <sys/resource.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

typedef int					t_bool;

typedef struct				s_mem_g
{
	void					*mem;
	size_t					size;
	struct s_mem_g			*next;
}							t_mem_g;

typedef struct			s_block
{
	size_t						size;
	struct s_block		*next;
	struct s_block		*prev;
	t_bool						free;
	void							*ptr;
}										t_block;

typedef struct				s_memory
{
	char					init;
	t_mem_g				*sml;
	t_mem_g				*med;
	t_block					*lrg;
}							t_memory;

extern t_memory						global_mem;
extern pthread_mutex_t		global_mutex;

void					*ft_malloc(size_t size);
void					*malloc(size_t size);
void					ft_free(void *ptr);
void					free(void *ptr);
void					*ft_realloc(void *ptr, size_t size);
void					*realloc(void *ptr, size_t size);
void					*calloc(size_t nitems, size_t size);
t_block				*new_mem_block(t_block *current, size_t size);
t_mem_g				*fusion(t_block *ptr, t_mem_g **prev);
t_mem_g				*find_mem(t_block *ptr, t_mem_g *mem_g, t_mem_g **prev);
void					extend_block(t_block *tmp, size_t size);
void					*ft_memcpy(void *dest, const void *src, size_t size);
int						ft_putnbr_base(size_t number, int base);
int						ft_putstr_mem(char *s);
t_mem_g				*new_mem_group(t_mem_g *current, size_t size);
void					ft_show_alloc_mem(void);
void					show_alloc_mem(void);

#endif
