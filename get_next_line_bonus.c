/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earriaga <earriaga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:48:20 by earriaga          #+#    #+#             */
/*   Updated: 2023/08/02 14:38:27 by earriaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

/**
 * @param strr
 * Returns the next string
 * The string starts in the next place from the '\n'
 * @return the resulting string
 */
static char	*ft_next_line(char *str)
{
	int		i;
	int		j;
	char	*right_line;

	right_line = NULL;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	right_line = (char *)malloc(ft_strlen(str) - i + 1);
	if (!right_line)
		return (NULL);
	j = 0;
	while (str[i++])
		right_line[j++] = str[i];
	right_line[j] = '\0';
	free(str);
	return (right_line);
}

/** 
 * @param str
 * Reads the content until a '\n' is found or the end 
 * of the string in case no new line is found.
 * @returns the new line including '\n' and '\0'
 */
static char	*ft_save_line(char *str)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	new_line = NULL;
	if (!str || !str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i ++;
	if (str[i] == '\n')
		new_line = (char *)malloc((i + 2));
	else
		new_line = (char *)malloc((i + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		new_line[j++] = str[i++];
	if (str[i] == '\n')
		new_line[j++] = str[i++];
	new_line[i] = '\0';
	return (new_line);
}

/**
 * @param fd
 * @param str
 * Reads from the File Descriptor a size of
 * BUFFER_SIZE until a '\n' is found.
 * Saves the content as its being read
 * @returns the read content or NULL in case of error
 */
static char	*ft_read_line(int fd, char *str)
{
	char	*buff;
	ssize_t	byread;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	byread = 1;
	while (!ft_strchr(str, '\n') && byread != 0)
	{
		byread = read(fd, buff, BUFFER_SIZE);
		if (byread < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[byread] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (str);
}

/**
 * @param fd
 * Reads from the File Descriptor
 * @returns returns a line or nothing if EOF
 */
char	*get_next_line(int fd)
{
	static char	*container[1024];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(container[fd]);
		container[fd] = NULL;
		return (NULL);
	}
	container[fd] = ft_read_line(fd, container[fd]);
	if (!container[fd])
		return (NULL);
	buffer = ft_save_line(container[fd]);
	if (!buffer)
	{
		free(container[fd]);
		container[fd] = NULL;
		return (NULL);
	}
	container[fd] = ft_next_line(container[fd]);
	if (!container[fd])
		return (NULL);
	return (buffer);
}
