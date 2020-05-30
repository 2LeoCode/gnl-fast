/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 17:56:37 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/30 16:01:29 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && (*s - c))
		s++;
	if (!*s)
		return (c ? NULL : (char*)s);
	return ((char*)s);
}

size_t	line_size(t_list *lstbuf)
{
	size_t	len;
	int		i;

	len = 0;
	while (lstbuf)
	{
		i = 0;
		while (lstbuf->buf[i] && (lstbuf->buf[i++] - '\n'))
			len++;
		lstbuf = lstbuf->next;
	}
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tmp;
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (s1 && s1[i++])
		size++;
	i = 0;
	while (s2 && s2[i++])
		size++;
	if (!(tmp = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (s1 && *s1)
		*(tmp++) = *(s1++);
	while (s2 && *s2)
		*(tmp++) = *(s2++);
	*tmp = 0;
	return (tmp - size);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[i++])
		len++;
	if (!(tmp = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s)
		*(tmp++) = *(s++);
	*tmp = 0;
	return (tmp - len);
}

int		ft_lstclear(t_list **to_free)
{
	t_list	*prev;

	if (!to_free || !*to_free)
		return (0);
	while (*to_free)
	{
		prev = *to_free;
		*to_free = (*to_free)->next;
		free(prev);
	}
	return (0);
}
