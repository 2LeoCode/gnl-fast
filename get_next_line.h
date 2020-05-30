/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 17:19:58 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/30 16:08:13 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif
# define MAX_FD 9999
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	char			buf[BUFFER_SIZE + 1];
	struct s_list	*next;
}					t_list;
typedef struct		s_buffer
{
	t_list			*lstbuf;
	t_list			*origin;
	char			*line;
}					t_buffer;
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
int					get_next_line(int fd, char **line);
size_t				line_size(t_list *lstbuf);
int					ft_lstclear(t_list **to_free);
#endif
