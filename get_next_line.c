/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyoshiha <iyoshiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:16:02 by iyoshiha          #+#    #+#             */
/*   Updated: 2021/12/12 20:47:14 by iyoshiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	manage_txt(char **save, t_txt *txt, int fd, t_txt_cmd command)
{
	if (command == init_txt)
	{
		txt->fd = fd;
		if (BUFFER_SIZE <= 0 || READ_ERR >= read(fd, NULL, 0))
			return (ERROR);
		if (BUFFER_SIZE > MAX_READ_BYTES)
			txt->bufsize = MAX_READ_BYTES;
		else
			txt->bufsize = BUFFER_SIZE;
		if (MEMORY_ERROR == manage_buf(malloc_buf, save, txt))
			return (ERROR);
		txt->save_len = 0;
		txt->newline_i = GNL_NL_NOT_FOUND;
	}
	if (NULL == save[fd])
		return (INIT_SUCCESS);
	while (save[fd][txt->save_len] != '\0')
	{
		if ((save[fd][txt->save_len++] == '\n') && (txt->newline_i == NO_NL))
			txt->newline_i = (txt->save_len OF_PREVIOUS);
	}
	if (command == find_newline)
		return (txt->newline_i);
	return (INIT_SUCCESS);
}

void	*manage_buf(t_buf_cmd command, char **save, t_txt *txt)
{
	char	*for_free;

	if (command == malloc_buf)
	{
		txt->buf = malloc(txt->bufsize + END_STR);
		if (txt->buf == NULL)
			return (NULL);
	}
	else if (command == save_buf)
	{
		txt->buf[txt->len_read] = '\0';
		if (FIRST_CALL == save[txt->fd])
		{
			save[txt->fd] = ft_strjoin(NULL, txt->buf);
			return (save[txt->fd]);
		}
		for_free = save[txt->fd];
		save[txt->fd] = ft_strjoin(for_free, txt->buf);
		free(for_free);
		return (save[txt->fd]);
	}
	else if (command == free_buf)
		free(txt->buf);
	return (MEMORY_SUCCESS);
}

void	*create_oneline(t_txt *txt, char **save)
{
	size_t	i;
	char	*old_save;

	i = 0;
	txt->line = malloc(txt->save_len + END_STR);
	if (NULL == txt->line)
		return (NULL);
	while (save[txt->fd][i] != '\0')
	{
		txt->line[i] = save[txt->fd][i];
		i = (NEXT i);
		if (save[txt->fd][(i OF_PREVIOUS)] == '\n')
			break ;
	}
	txt->line[i] = '\0';
	if ((END_OF_FILE == txt->len_read) \
	&& (GNL_NL_NOT_FOUND == txt->newline_i))
		return (save_free(save, txt, in_create_newline));
	old_save = save[txt->fd];
	save[txt->fd] = ft_strjoin(NULL, (old_save + (NEXT txt->newline_i)));
	free(old_save);
	return (save[txt->fd]);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	t_txt		txt;

	if (READ_ERR == manage_txt(save, &txt, fd, init_txt))
		return (ERROR_OR_DONE);
	while (1)
	{
		if (ERROR_OR_DONE == read_txt(save, &txt))
			return (ERROR_OR_DONE);
		if (END_OF_FILE == txt.len_read)
			break ;
		if (MEMORY_ERROR == manage_buf(save_buf, save, &txt))
		{
			manage_buf(free_buf, save, &txt);
			return (MEMORY_ERROR);
		}
		if (GNL_NL_NOT_FOUND != manage_txt(save, &txt, fd, find_newline))
			break ;
	}
	manage_buf(free_buf, save, &txt);
	if ((END_OF_FILE == txt.len_read) && '\0' == save[fd][0])
		return (save_free(save, &txt, in_gnl));
	if (NULL == create_oneline(&txt, save))
		return (MEMORY_ERROR);
	return (txt.line);
}
