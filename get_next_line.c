/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:18 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/24 19:16:24 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_update_buf_info(t_read_buffer *buf, t_ret_line *line)
{
	if (buf->read_bytes <= 0 || buf->index_tail >= buf->read_bytes)
	{
		buf->index_tail = 0;
		buf->f_end_line = 0;
		return 0;
	}
	if (buf->index_tail > 0)
	{
		line->size = BUFFER_SIZE + 1;
		line->res = (char*)malloc(line->size);
		if (!line->res)
			return (-1);
		while(buf->index_tail < buf->read_bytes && buf->read_text[buf->index_tail] != '\n')
		{
			line->res[line->len] = buf->read_text[buf->index_tail];
			buf->index_tail++;
			line->len++;
		}
		if (buf->index_tail < buf->read_bytes && buf->read_text[buf->index_tail] == '\n')
		{
			line->res[line->len] = '\n';
			line->len++;
			line->res[line->len] = '\0';
			buf->f_end_line = 1;
			buf->index_tail++;
			return (1); // есть готовая строка
		}
	}
	buf->index_tail = 0;
	buf->f_end_line = 0;
	return (0);
}

int	ft_create_line(t_read_buffer *buf, t_ret_line *line)
{
	char	*tmp;
	size_t	i;
	size_t	read_bytes;
	
	i = 0;
	read_bytes = (size_t)buf->read_bytes;
	if (line->size - line->len < read_bytes + 1)
	{
		tmp = line->res;
		line->size = (line->size + read_bytes + 1) * 2;
		line->res = (char*)malloc(line->size * sizeof(char));
		if (!line->res)
		{
			ft_liberator(tmp);
			return (-1);
		}	
		while(i < line->len)
		{
			line->res[i] = tmp[i];
			i++;
		}
		line->res[line->len] = '\0';
		ft_liberator(tmp);
		i = 0;
	}
	while(i < read_bytes && buf->read_text[i] != '\n')
	{
		line->res[line->len] = buf->read_text[i];
		line->len++;
		i++;
	}
	if (i < read_bytes && buf->read_text[i] == '\n')
	{
		line->res[line->len] = '\n';
		line->len++;
		line->res[line->len] = '\0';
		buf->index_tail = i + 1;
		buf->f_end_line = 1;
	}
	return (1);
}

static int	ft_check_read_text(t_read_buffer *buf, t_ret_line *line)
{
	if (buf->read_bytes == 0)
	{
		if (line->len > 0)
		{
			buf->f_end_line = 1;
			line->res[line->len] = '\0';
			return (1);
		}
		ft_liberator(line->res);
		buf->f_end_line = 1;
   		return (1);
	}
	if (!line->res)
	{
		// line->size = ft_line_len(buf) + 1;
		// if (line->size < (size_t)buf->read_bytes)
		// 	buf->index_tail = line->size;
		line->size = (size_t)buf->read_bytes + 1;
		line->res = (char*)malloc(line->size * sizeof(char));
		if (!line->res)
			return (-1);
	}
	return (ft_create_line(buf, line));	
}

char	*get_next_line(int fd)
{
	static t_read_buffer buf;
	t_ret_line line = {0};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf.f_end_line == 1)
		if (ft_update_buf_info(&buf, &line) == - 1) 
			return (NULL); 
	while (buf.f_end_line != 1)
	{
		buf.read_bytes = read(fd, buf.read_text, BUFFER_SIZE);
		if (buf.read_bytes == -1)
		{
			ft_set_zero_buf(&buf);
			ft_liberator(line.res);
			return(NULL);
		}
		if (ft_check_read_text(&buf, &line) == -1)
		{	
			ft_liberator(line.res);
			return (NULL);
		}
	}
	if (line.len < line.size)
	{
		//printf("1 s = %s, len = %ld, size = %ld, strlen %ld\n", line.res, line.len, line.size, strlen(line.res));
		size_t i = 0;
		char *tmp;

		tmp = line.res;
		line.size = line.len + 1;
		line.res = (char*)malloc(line.size * sizeof(char));
		if (!line.res)
		{
			ft_liberator(tmp);
			return (NULL);
		}	
		while(i < line.len)
		{
			line.res[i] = tmp[i];
			i++;
		}
		line.res[line.len] = '\0';
		ft_liberator(tmp);
	}
	//printf("2 s = %s, len = %ld, size = %ld, strlen %ld\n", line.res, line.len, line.size, strlen(line.res));
	return (line.res);
}
