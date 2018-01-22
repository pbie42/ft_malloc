/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 16:33:06 by pbie              #+#    #+#             */
/*   Updated: 2016/04/23 16:33:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	check4_newline(char buff[])
{
	size_t i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	return (i);
}

char	*fill_stockage(char *tmp, char *buff, size_t length)
{
	size_t		i;
	size_t		j;
	char		*rslt;

	i = 0;
	j = 0;
	rslt = ft_strnew(ft_strlen(tmp) + length + 1);
	while (tmp[i])
	{
		rslt[i] = tmp[i];
		i++;
	}
	while (j < length)
	{
		rslt[i] = buff[j];
		i++;
		j++;
	}
	free(tmp);
	return (rslt);
}

void	shift_buffer(char buff[], size_t length, char **line)
{
	int i;

	i = 0;
	if (buff[0] == '\0' && *line != '\0')
		return ;
	else
	{
		while (buff[i + length + 1] != '\0')
		{
			buff[i] = buff[i + length + 1];
			i++;
		}
		while (i < BUFF_SIZE)
		{
			buff[i] = '\0';
			i++;
		}
		return ;
	}
}

int		ft_get_next_line(int const fd, char **line)
{
	static char		buff[BUFF_SIZE + 1] = {'\0'};
	int				red;
	size_t			length;

	if (line == NULL)
		return (-1);
	red = 1;
	*line = ft_strnew(1);
	while (red > 0)
	{
		if (buff[0] == '\0')
			red = read(fd, buff, BUFF_SIZE);
		if (red < 0)
			return (-1);
		length = check4_newline(buff);
		*line = fill_stockage(*line, buff, length);
		if (buff[length] != '\0' || (buff[0] == '\0' && *line[0] != '\0'))
		{
			shift_buffer(buff, length, line);
			return (1);
		}
		ft_strclr(buff);
	}
	return (0);
}
