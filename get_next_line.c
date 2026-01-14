/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azidouh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:41:31 by azidouh           #+#    #+#             */
/*   Updated: 2025/12/05 11:41:33 by azidouh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_modify(char **tmp)
{
	char	*save_tmp;

	if (!*tmp || !ft_strchr(*tmp, '\n'))
	{
		free(*tmp);
		*tmp = NULL;
		return ;
	}
	save_tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	free(*tmp);
	*tmp = save_tmp;
	if (**tmp == '\0')
	{
		free(*tmp);
		*tmp = NULL;
	}
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	size_t	len1;
	size_t	len2;
	char	*joined_str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = malloc((total_size));
	if (!joined_str)
		return (NULL);
	ft_memcpy(joined_str, s1, len1);
	ft_memcpy(joined_str + len1, s2, len2);
	joined_str[len1 + len2] = '\0';
	return (joined_str);
}

static char	*copy(char *tmp, char *buff)
{
	char	*save_tmp;

	if (!tmp)
		return (ft_strdup(buff));
	save_tmp = ft_strjoin(tmp, buff);
	free(tmp);
	return (save_tmp);
}

static char	*get_line(char **tmp, ssize_t len)
{
	char	*line;

	if (!tmp || !*tmp)
		return (NULL);
	if (ft_strchr(*tmp, '\n'))
	{
		line = ft_substr(*tmp, 0, ft_strchr(*tmp, '\n') - *tmp + 1);
		ft_modify(tmp);
		return (line);
	}
	if (len == 0)
	{
		if (**tmp)
		{
			line = ft_strdup(*tmp);
			free(*tmp);
			*tmp = NULL;
			return (line);
		}
		free(*tmp);
		*tmp = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buff;
	ssize_t		len_read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	len_read_bytes = 1;
	while (len_read_bytes != 0)
	{
		len_read_bytes = read(fd, buff, BUFFER_SIZE);
		if (len_read_bytes < 0)
			return (free(buff), free(tmp), tmp = NULL, NULL);
		if (len_read_bytes == 0)
			break ;
		buff[len_read_bytes] = '\0';
		tmp = copy(tmp, buff);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(buff);
	return (get_line(&tmp, len_read_bytes));
}
