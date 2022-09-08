/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adohou <adohou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:32:54 by adohou            #+#    #+#             */
/*   Updated: 2022/09/07 21:41:21 by adohou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_mcopy(char * s)
{
	char	*cpy;
	int		len;
	int		i;
	len = ft_strlen(s);
	cpy = (char*)malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static char	*read_and_store(int fd, char *buffer)
{
	char	*store;
	int		res;

	store = get_mcopy(buffer);
	if (!store)
		return (NULL);
	ft_memset(buffer, 0, BUFFER_SIZE - 1);
	res = 1;
	while (res > 0 && !ft_strchr(buffer, '\n'))
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
		{
			free(store);
			return (NULL);
		}
		buffer[res] = '\0';
		if (res == 0 && !store[0])
		{
			free(store);
			return(NULL);
		}
		store = ft_strjoin(store, buffer);
	}

	return (store);
}

char	*get_current_line(char *store)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	line = (char*)malloc(sizeof(char) * i + 1);
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

void	get_new_buffer(char *store, char *buffer)
{
	int		i;
	int		j;

	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	j = 0;
	while (store[i])
		buffer[j++] = store[i++];
	buffer[j] = '\0';
	// return (buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) == -1)
		return (NULL);
	store = read_and_store(fd, buffer);
	if (!store)
		return (NULL);
	line = get_current_line(store);
	get_new_buffer(store , buffer);
	free(store);

	return (line);
}
