/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 17:21:53 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/30 15:37:58 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		update_buffer(char **line, char **left, char *lst_line)
{
	char	*tmp;
	char	*tmp2;

	if (lst_line)
	{
		*line = ft_strjoin(*left, lst_line);
		if (*left)
			free(*left);
		return (line ? 0 : -1);
	}
	tmp = ft_strdup(*left);
	free(*left);
	if (!tmp)
		return (-1);
	tmp2 = ft_strchr(tmp, '\n');
	*left = *(tmp2 + 1) ? ft_strdup(tmp2 + 1) : NULL;
	*tmp2 = 0;
	if (!(*line = ft_strdup(tmp)))
		free(*left);
	free(tmp);
	return (line ? 1 : -1);
}

char	*get_whats_left(t_list *lstbuf)
{
	char	*tmp;
	int		i;

	while (lstbuf)
	{
		i = 0;
		while (lstbuf->buf[i] && (lstbuf->buf[i] - '\n'))
			i++;
		if (lstbuf->buf[i] == '\n')
		{
			tmp = &lstbuf->buf[i + 1];
			return (ft_strdup(tmp));
		}
		lstbuf = lstbuf->next;
	}
	return (ft_strdup(""));
}

t_list		*read_to_list(int fd)
{
	t_list	*begin;
	t_list	*tmp;
	int		ret;

	if (!(tmp = malloc(sizeof(t_list))))
		return (NULL);
	tmp->next = NULL;
	begin = tmp;
	while (1)
	{
		ret = read(fd, tmp->buf, BUFFER_SIZE);
		tmp->buf[ret * (ret > 0)] = 0;
		if (!ret || ft_strchr(tmp->buf, '\n'))
			return (begin);
		if ((ret < 0) || !(tmp->next = malloc(sizeof(t_list))))
		{
			ft_lstclear(&begin);
			return (NULL);
		}
		tmp = tmp->next;
		tmp->next = NULL;
	}
	return (begin);
}

char		*get_line_from_list(t_list *lstbuf)
{
	t_list	*tmp;
	char	*line;
	size_t	len;
	int		i;

	tmp = lstbuf;
	len = line_size(lstbuf);
	if (!(line = (char*)malloc(sizeof(char) * (len + 1))))
	{
		ft_lstclear(&tmp);
		return (NULL);
	}
	while(tmp)
	{
		i = 0;
		while (tmp->buf[i] && (tmp->buf[i++] - '\n'))
			*(line++) = tmp->buf[i - 1];
		tmp = tmp->next;
	}
	*line = 0;
	return (line - len);
}

int			get_next_line(int fd, char **line)
{
	t_buffer		buffer;
	static char		*left[MAX_FD];
	int				ret;

	buffer.line = NULL;
	buffer.lstbuf = NULL;
	if (BUFFER_SIZE < 1 || (((left[fd] && !ft_strchr(left[fd], '\n'))
	|| !left[fd]) && (!(buffer.lstbuf = read_to_list(fd))
	|| !(buffer.line = get_line_from_list(buffer.lstbuf))))
	|| ((ret = update_buffer(line, &left[fd], buffer.line)) < 0)
	|| !*line
	|| (buffer.lstbuf && !(left[fd] = get_whats_left(buffer.lstbuf))))
		return (ft_lstclear(&buffer.lstbuf) - 1);
	if (buffer.line)
		free(buffer.line);
	buffer.line = NULL;
	buffer.origin = buffer.lstbuf;
	while (buffer.lstbuf)
	{
		if (ft_strchr(buffer.lstbuf->buf, '\n'))
			return (ft_lstclear(&buffer.origin) + 1);
		buffer.lstbuf = buffer.lstbuf->next;
	}
	if (ret)
		return (ft_lstclear(&buffer.origin) + 1);
	free(left[fd]);
	left[fd] = NULL;
	return (ft_lstclear(&buffer.origin));
}
