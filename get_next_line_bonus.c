/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:34:39 by gmohamed          #+#    #+#             */
/*   Updated: 2024/07/22 19:35:12 by gmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	if (s1)
		ft_memcpy(joined_str, s1, len1);
	if (s2)
		ft_memcpy(joined_str + len1, s2, len2);
	joined_str[len1 + len2] = '\0';
	free((char *)s1);
	return (joined_str);
}

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	if (left_str && ft_strchr(left_str, '\n'))
		return (left_str);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	rd_bytes = 1;
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(left_str);
			return (0);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (free(buff), left_str);
}

char	*ft_get_line(char *left_str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_left_str(char *left_str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(left_str) - i);
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		new_str[j++] = left_str[i++];
	new_str[j] = '\0';
	free(left_str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffers[fd])
	{
		buffers[fd] = malloc(1);
		if (!buffers[fd])
			return (NULL);
		buffers[fd][0] = '\0';
	}
	buffers[fd] = ft_read_to_left_str(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = ft_get_line(buffers[fd]);
	buffers[fd] = ft_new_left_str(buffers[fd]);
	return (line);
}
