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

char	*copy(char *tmp, char *buff)
{
	char	*save_tmp;
	ssize_t	len;

	len = 0;
	save_tmp = NULL;
	if (tmp)
	{
		save_tmp = ft_strdup(tmp);
		free(tmp);
		len = ft_strlen(save_tmp) + ft_strlen(buff);
		tmp = malloc(len + 1);
		if (!tmp)
			return (NULL);
		ft_memcpy(tmp, save_tmp, ft_strlen(save_tmp) + 1);
		tmp[ft_strlen(save_tmp)] = '\0';
		ft_memcpy(ft_strchr(tmp, '\0'), buff, ft_strlen(buff));
		tmp[len] = '\0';
		free(save_tmp);
	}
	else if (!tmp)
		tmp = ft_strdup(buff);
	return (tmp);
}

void	ft_modify(char **tmp)
{
	char	*save_tmp;

	save_tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	free(*tmp);
	*tmp = save_tmp;
}

char	*get_line(char **tmp, char **buff, ssize_t len)
{
	char	*line;

	line = NULL;
	if (*tmp && **tmp && len == 0)
	{
		line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		free(*buff);
		*buff = NULL;
		return (line);
	}
	if (ft_strchr(*tmp, '\n') != NULL)
	{
		line = ft_substr(*tmp, 0, (ft_strlen(*tmp) - ft_strlen(ft_strchr(*tmp,
							'\n'))) + 1);
		ft_modify(tmp);
		return (line);
	}
	free(*tmp);
	*tmp = NULL;
	free(*buff);
	*buff = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buff;
	ssize_t		len_read_bytes;

	buff = NULL;
	len_read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (len_read_bytes != 0)
	{
		if (tmp && ft_strchr(tmp, '\n') != NULL)
			return (get_line(&tmp, &buff, len_read_bytes));
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		len_read_bytes = read(fd, buff, BUFFER_SIZE);
		if (len_read_bytes <= 0)
			break ;
		buff[len_read_bytes] = '\0';
		tmp = copy(tmp, buff);
		free(buff);
		buff = NULL;
	}
	return (get_line(&tmp, &buff, len_read_bytes));
}
