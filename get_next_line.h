/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhmeto <aakhmeto@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:37:21 by aakhmeto          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:08 by aakhmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_read_buffer
{
	char	read_text[BUFFER_SIZE + 1];
	ssize_t	read_bytes;
	size_t	index_tail;
	int		f_end_line;
}	t_read_buffer;
typedef struct s_ret_line
{
	char	*res;
	size_t	len;
	size_t	size;
}	t_ret_line;
char	*get_next_line(int fd);
void	ft_set_zero_buf(t_read_buffer *buf);
void	ft_liberator(char *str);
int		ft_line_realloc(t_ret_line *line, size_t new_size);
int		ft_check_end_line(t_read_buffer *buf, t_ret_line *line, int index);
void	ft_set_zero_line(t_ret_line *line);

#endif