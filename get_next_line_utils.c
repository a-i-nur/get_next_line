/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhmeto <aakhmeto@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:15 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:55 by aakhmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_set_zero_buf(t_read_buffer *buf)
{
	buf->index_tail = 0;
	buf->f_end_line = 0;
	buf->read_bytes = 0;
}

void	ft_liberator(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

int	ft_line_realloc(t_ret_line *line, size_t new_size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = line->res;
	line->size = new_size;
	line->res = (char *)malloc(line->size * sizeof(char));
	if (!line->res)
	{
		ft_liberator(tmp);
		return (-1);
	}	
	while (i < line->len)
	{
		line->res[i] = tmp[i];
		i++;
	}
	line->res[line->len] = '\0';
	ft_liberator(tmp);
	return (1);
}

int	ft_check_end_line(t_read_buffer *buf, t_ret_line *line, int index)
{
	if (index < buf->read_bytes && buf->read_text[index] == '\n')
	{
		line->res[line->len] = '\n';
		line->len++;
		line->res[line->len] = '\0';
		buf->f_end_line = 1;
		buf->index_tail = index + 1;
		return (1);
	}
	return (0);
}

void	ft_set_zero_line(t_ret_line *line)
{
	line->res = NULL;
	line->len = 0;
	line->size = 0;
}
