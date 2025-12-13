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

void	ft_modify(char **tmp)
{
	char	*save_tmp;

	if (!*tmp || !ft_strchr(*tmp, '\n'))
		return ;
	save_tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	free(*tmp);
	*tmp = save_tmp;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	size_t	len1;
	size_t	len2;
	char	*joined_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = malloc((total_size));
	if (!joined_str)
		return (NULL);
	ft_memcpy(joined_str, s1, len1);
	ft_memcpy(joined_str + len1, s2, len2);
	joined_str[len1 + len2] = '\0';
	return (joined_str);
}

char	*copy(char *tmp, char *buff)
{
	char	*save_tmp;

	if (!tmp)
		return (ft_strdup(buff));
	save_tmp = ft_strjoin(tmp, buff);
	free(tmp);
	return (save_tmp);
}

char	*get_line(char **tmp, ssize_t len)
{
	char	*line;

	if (!tmp || !*tmp)
		return (NULL);
	if (len == 0 && **tmp)
	{
		line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		return (line);
	}
	if (ft_strchr(*tmp, '\n') != NULL)
	{
		line = ft_substr(*tmp, 0, ft_strchr(*tmp, '\n') - *tmp + 1);
		ft_modify(tmp);
		return (line);
	}
	return (NULL);
}

// char	*get_next_line(int fd)
// {
// 	static char	*tmp;
// 	char		*buff;
// 	ssize_t		len_read_bytes;

// 	1 && (buff = NULL, len_read_bytes = 1);
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (len_read_bytes != 0)
// 	{
// 		buff = malloc(BUFFER_SIZE + 1);
// 		if (!buff)
// 			return (NULL);
// 		len_read_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (len_read_bytes <= 0)
// 		{
// 			free(buff);
// 			break ;
// 		}
// 		buff[len_read_bytes] = '\0';
// 		tmp = copy(tmp, buff);
// 		free(buff);
// 		if (ft_strchr(tmp, '\n'))
// 			break ;
// 	}
// 	return (get_line(&tmp, len_read_bytes));
// }

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
		if (len_read_bytes <= 0)
			break;
		buff[len_read_bytes] = '\0';
		tmp = copy(tmp, buff);
		if (ft_strchr(tmp, '\n'))
			break;
	}
	free(buff);
	return (get_line(&tmp, len_read_bytes));
}

