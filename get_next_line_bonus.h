/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:21 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/24 18:52:06 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef struct s_read_buffer
{
	char        read_text[BUFFER_SIZE];
	ssize_t     read_bytes;
	ssize_t		index_tail;
	int         f_end_line;
}   t_read_buffer;
typedef struct s_ret_line
{
	char        *res;
	size_t     len;
	size_t     size;
}   t_ret_line;
char	*get_next_line(int fd);
void	ft_set_zero_buf(t_read_buffer *buf);
void	ft_liberator(char *str);
size_t	ft_line_len(t_read_buffer *buf);

# endif