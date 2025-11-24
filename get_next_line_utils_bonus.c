/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:15 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/24 18:31:02 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    ft_set_zero_buf(t_read_buffer *buf)
{
	buf->index_tail = 0;
	buf->f_end_line = 0;
	buf->read_bytes = 0;
}

void    ft_liberator(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

size_t ft_line_len(t_read_buffer *buf)
{
	size_t	i;
	size_t	read_bytes;
	
	i = 0;
	read_bytes = (size_t)buf->read_bytes;
	while(i < read_bytes && buf->read_text[i] != '\n')
	{
		i++;
	}
	return i;
}
