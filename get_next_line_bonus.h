/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyoshiha <iyoshiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:49:18 by iyoshiha          #+#    #+#             */
/*   Updated: 2021/12/12 20:51:30 by iyoshiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define MAX_READ_BYTES 0x7ffff000
# define END_OF_FILE 0
# define READ_ERR -1
# define ERROR -1
# define INIT_SUCCESS 1
# define FIRST_CALL ((void *)0)
# define DONE ((void *)0)
# define ERROR_OR_DONE ((void *)0)
# define MEMORY_SUCCESS ((void *)0x7fffff)
# define MEMORY_ERROR ((void *)0)
# define END_STR 1
# define NEXT 1+
# define OF_PREVIOUS -1
# define CONVERT_TO_LEN 1+
# define GNL_NL_NOT_FOUND -1
# define NO_NL -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef void*	t_error;

typedef struct s_txt
{
	size_t	save_len;
	ssize_t	newline_i;
	ssize_t	len_read;
	int		bufsize;
	int		fd;
	char	*buf;
	char	*line;
}				t_txt;

typedef enum e_buf_cmd
{
	save_buf,
	malloc_buf,
	free_buf
}			t_buf_cmd;

typedef enum e_place_save
{
	in_create_newline,
	in_gnl
}			t_place_save;

typedef enum e_txt_cmd
{
	init_txt,
	find_newline
}			t_txt_cmd;

char	*ft_strjoin(char const *head, char const *tail);
ssize_t	manage_txt(char **save, t_txt *txt, int fd, t_txt_cmd command);
void	*manage_buf(t_buf_cmd command, char **save, t_txt *txt);
void	*save_free(char **save, t_txt *txt, t_place_save place);
void	*create_oneline(t_txt *txt, char **save);
char	*get_next_line(int	fd);
void	*read_txt(char **save, t_txt *txt);
size_t	ft_strlen(const char *s);

#endif
