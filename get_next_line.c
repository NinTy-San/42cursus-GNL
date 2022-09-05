/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adohou <adohou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:32:54 by adohou            #+#    #+#             */
/*   Updated: 2022/09/05 19:14:14 by adohou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *reader, char *store)
{
	free(reader);
	if (!store || store[0] == 0)
	{
		free(store);
		return (NULL);
	}
	return (store);
}

static char	*read_and_store(int fd, char *store)
{
	char	*reader;
	int		res;

	reader = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	if (!store)
	{
		store = (char *)malloc(sizeof(char) * 1);
		store[0] = '\0';
	}
	res = 1;
	while (res > 0 && !ft_strchr(store, '\n'))
	{
		ft_memset(reader, 0, BUFFER_SIZE + 1);
		res = read(fd, reader, BUFFER_SIZE);
		if (res <= 0 && !reader[0])
			return (ft_free(reader, store));
		reader[res] = '\0';
		if (res == 0)
			break ;
		store = ft_strjoin(store, reader);
	}
	free(reader);
	return (store);
}

static char	*get_current_line(char *store)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i--;
	j = 0;
	while (j <= i)
	{
		line[j] = store[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*get_new_store(char *store)
{
	char	*new_store;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(store);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	new_store = malloc(sizeof(char) * (len - i + 1));
	if (!new_store)
		return (NULL);
	j = 0;
	while (i < len)
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*tmp;
	char		*line;

	tmp = store;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	tmp = read_and_store(fd, tmp);
	if (!tmp)
		return (NULL);
	line = get_current_line(tmp);
	if (!line)
		return (NULL);
	store = get_new_store(tmp);
	free(tmp);
	return (line);
}
