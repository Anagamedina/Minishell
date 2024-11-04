/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:51:56 by anamedin          #+#    #+#             */
/*   Updated: 2024/08/01 13:31:01 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*clean_storage(char *storage, char *read_storage, int bytes_read)
{
	char	*new_storage;

	new_storage = NULL;
	if (bytes_read > 0)
	{
		new_storage = ft_strjoin(storage, read_storage);
		if (new_storage == NULL)
		{
			ft_free(&storage);
			return (NULL);
		}
		ft_free(&storage);
	}
	if (bytes_read == 0)
		new_storage = storage;
	return (new_storage);
}

char	*initial_buffer(char *storage)
{
	char	*buf;

	buf = storage;
	if (buf == NULL)
	{
		buf = (char *)malloc(sizeof(char));
		if (buf == NULL)
			return (NULL);
		*buf = '\0';
	}
	return (buf);
}

static char	*update_line_from_storage(char **storage, int bytes_read)
{
	char	*line;
	int		jump;
	char	*tmp;
	size_t	len;

	line = NULL;
	len = ft_strlen(*storage);
	jump = ft_strchr_c(*storage, '\n');
	if (jump >= 0)
	{
		line = ft_substr(*storage, 0, jump + 1);
		tmp = *storage;
		*storage = ft_substr(*storage, jump + 1, len);
		ft_free(&tmp);
		return (line);
	}
	if (bytes_read == 0)
	{
		line = ft_substr(*storage, 0, len);
		*storage = ft_free(storage);
	}
	return (line);
}

static char	*line_read(char **storage, int fd)
{
	char	*read_storage;
	char	*line;
	int		bytes;

	read_storage = (char *)malloc(BUFFER_SIZE + 1);
	if (read_storage == NULL)
		return (NULL);
	line = NULL;
	while (line == NULL)
	{
		bytes = read(fd, read_storage, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(&read_storage));
		read_storage[bytes] = '\0';
		*storage = clean_storage(*storage, read_storage, bytes);
		if (*storage == NULL)
			return (ft_free(&read_storage));
		line = update_line_from_storage(storage, bytes);
	}
	free(read_storage);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line;

	if ((fd < 0 || BUFFER_SIZE <= 0))
	{
		return (ft_free(&storage), NULL);
	}
	storage = initial_buffer(storage);
	if (storage == NULL)
		return (NULL);
	line = line_read(&storage, fd);
	if (line == NULL)
	{
		return (ft_free(&storage), NULL);
	}
	if (line != NULL && ft_strlen(line) == 0)
	{
		ft_free(&line);
		return (NULL);
	}
	return (line);
}
