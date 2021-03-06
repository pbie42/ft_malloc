/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <pbie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2018/01/30 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		ft_putstr_mem(char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	s_cpy = s;
	while (s_cpy && *s_cpy && ++i)
		++s_cpy;
	return (write(1, s, i));
}
