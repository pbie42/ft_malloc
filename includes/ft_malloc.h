/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/09/29 15:19:02 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TRUE 1
# define FALSE 0
# define STOP "\033[0;0m"
# define EOC "\033[39m"
# define EOBG "\033[49m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[1m"
# define BLACK "\033[30m"
# define WHITE "\033[97m"
# define BWHITE "\033[1;97m"
# define BLUE "\033[34m"
# define RED "\033[31m"
# define BRED "\033[1;31m"
# define GREEN "\033[32m"
# define BGREEN "\033[1;32m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define BMAGENTA "\033[1;35m"
# define CYAN "\033[36m"
# define BCYAN "\033[1;36m"
# define GRAY "\033[37m"
# define BGBLACK "\033[40m"
# define BGRED "\033[41m"
# define BGGREEN "\033[42m"
# define BGYELLOW "\033[43m"
# define BGBLUE "\033[44m"
# define BGMAGENTA "\033[45m"
# define BGCYAN "\033[1;46m"
# define BGLIGHT "\033[1;47m"
# define BGGRAY "\033[47m"
# define INVWHITE "\033[7;97m"
# define INVCYAN "\033[7;36m"
# define INVRED "\033[7;31m"
# define INVMAGENTA "\033[7;35m"
# define SML 512
# define MED 4096
# define PROT PROT_READ|PROT_WRITE
# define ANON MAP_PRIVATE|MAP_ANONYMOUS

# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <ftw.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <err.h>
# include <termcap.h>
# include "../libft/includes/libftprintf.h"
# include <term.h>

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

extern t_memory				global_mem;

void					*ft_malloc(size_t size);
void					ft_free(void *ptr);
t_block				*new_mem_block(t_block *current, size_t size);
t_mem_g				*fusion(t_block *ptr, t_mem_g **prev);
t_mem_g				*find_mem(t_block *ptr, t_mem_g *mem_g, t_mem_g **prev);
void					extend_block(t_block *tmp, size_t size);
void					*ft_memcpy(void *dest, const void *src, size_t size);
int						ft_putnbr_base(size_t number, int base);
int						ft_putstr_mem(char *s);

#endif
