/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhmeto <aakhmeto@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:18 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/21 18:33:39 by aakhmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void ft_liberator(char **tail_read)
{
	if (tail_read)
	{
		free(*tail_read);
		*tail_read = NULL;
	}
}

static int 	ft_get_len_line(const char *buf_read, int res_read)
{
	int	i;

	i = 0;
	while(i < res_read && buf_read[i] != '\n')
		i++;
	if (buf_read[i] == '\n')
		i++;	
	return (i);
}

static char* ft_line_copy(const char *buf_read, int len_line)
{
	char *line;
	int	i;

	line = (char *)malloc(len_line + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len_line)
	{
		line[i] = buf_read[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_create_line(const char *buf_read, int res_read, char *tail_read)
{
	int		len_line;
	int 	len_tail;

	len_line = ft_get_len_line(buf_read, res_read);
	len_tail = res_read - len_tail;
	if (len_tail < res_read)
	{
		if (!tail_read)
		{
			return(ft_line_copy(buf_read, len_line));
		}
		else
		{
			return(ft_strjoin(tail_read, ))
		}
		
	}
	// create_tail
} 	

char	*get_next_line(int fd)
{
	static char	*tail_read;
	char		buf_read[BUFFER_SIZE];
	char		*line;
	int			res_read;

	res_read = read(fd, buf_read, BUFFER_SIZE);
	if (res_read = -1)
	{
		ft_leberator(&tail_read);
		return (NULL);
	}
	else
	{
		line = ft_create_line(buf_read, res_read, tail_read);
		if (!line)
		{
			ft_leberator(&tail_read);
			return (NULL);
		}
	}
	if (res_read == 0)
		ft_liberator(&tail_read);
	return (line);
}

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c -o gnl
// valgrind --leak-check=full --show-leak-kinds=all ./gnl
