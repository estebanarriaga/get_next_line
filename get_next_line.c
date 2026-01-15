/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earriaga <earriaga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:48:20 by earriaga          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by earriaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Global buffer array - one per file descriptor for multi-fd support
** Initialized to NULL; buffers are created lazily on first read
*/
static t_gnl_buffer	*g_buffers[GNL_MAX_FD];

/**
 * gnl_get_buffer - Get or create buffer for a file descriptor
 * @fd: File descriptor
 *
 * Lazily allocates a buffer structure for the fd on first access.
 * Uses calloc to ensure all fields are zero-initialized.
 *
 * Return: Pointer to buffer, or NULL on allocation failure
 */
static t_gnl_buffer	*gnl_get_buffer(int fd)
{
	t_gnl_buffer	*buf;

	if (g_buffers[fd])
		return (g_buffers[fd]);
	buf = calloc(1, sizeof(t_gnl_buffer));
	if (!buf)
		return (NULL);
	buf->data = malloc(GNL_BUFFER_SIZE);
	if (!buf->data)
	{
		free(buf);
		return (NULL);
	}
	buf->size = GNL_BUFFER_SIZE;
	buf->len = 0;
	buf->eof_reached = 0;
	g_buffers[fd] = buf;
	return (buf);
}

/**
 * gnl_ensure_capacity - Ensure buffer has enough space
 * @buf:    Buffer structure
 * @needed: Minimum free bytes required
 *
 * Uses doubling strategy to minimize reallocations.
 * Grows buffer exponentially until sufficient space available.
 *
 * Return: 0 on success, -1 on allocation failure
 */
static int	gnl_ensure_capacity(t_gnl_buffer *buf, size_t needed)
{
	size_t	new_size;
	char	*new_data;

	if (buf->size - buf->len >= needed)
		return (0);
	new_size = buf->size;
	while (new_size - buf->len < needed)
		new_size *= 2;
	new_data = realloc(buf->data, new_size);
	if (!new_data)
		return (-1);
	buf->data = new_data;
	buf->size = new_size;
	return (0);
}

/**
 * gnl_extract_line - Extract line from buffer up to delimiter position
 * @buf:       Buffer structure
 * @delim_pos: Position of delimiter in buffer (or last char position)
 *
 * Allocates new string containing data up to and including delim_pos.
 * Uses memmove to shift remaining data to front of buffer.
 * This avoids repeated malloc/free cycles.
 *
 * Return: Allocated line string (caller must free), or NULL on failure
 */
static char	*gnl_extract_line(t_gnl_buffer *buf, size_t delim_pos)
{
	char	*line;
	size_t	line_len;
	size_t	remaining;

	line_len = delim_pos + 1;
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	memcpy(line, buf->data, line_len);
	line[line_len] = '\0';
	remaining = buf->len - line_len;
	if (remaining > 0)
		memmove(buf->data, buf->data + line_len, remaining);
	buf->len = remaining;
	return (line);
}

/**
 * gnl_fill_buffer - Read more data from fd into buffer
 * @fd:  File descriptor
 * @buf: Buffer structure
 *
 * Ensures sufficient capacity, then reads directly into buffer.
 * Sets eof_reached flag when read returns 0.
 *
 * Return: Bytes read (>= 0), or -1 on error
 */
static ssize_t	gnl_fill_buffer(int fd, t_gnl_buffer *buf)
{
	ssize_t	bytes_read;

	if (gnl_ensure_capacity(buf, GNL_BUFFER_SIZE) < 0)
		return (-1);
	bytes_read = read(fd, buf->data + buf->len, GNL_BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
		buf->eof_reached = 1;
	buf->len += bytes_read;
	return (bytes_read);
}

/**
 * gnl_find_delim - Find delimiter in buffer
 * @buf:   Buffer structure
 * @delim: Delimiter character to search for
 *
 * Uses memchr for efficient SIMD-optimized search.
 * Handles binary data correctly (doesn't rely on null-termination).
 *
 * Return: Position of delimiter, or -1 if not found
 */
static ssize_t	gnl_find_delim(t_gnl_buffer *buf, char delim)
{
	char	*found;

	if (buf->len == 0)
		return (-1);
	found = memchr(buf->data, delim, buf->len);
	if (found)
		return (found - buf->data);
	return (-1);
}

/**
 * get_next_line_delim - Read next delimited segment from fd
 * @fd:    File descriptor to read from
 * @line:  Pointer to store allocated line (caller must free)
 * @delim: Delimiter character
 *
 * Main algorithm:
 * 1. Validate inputs (fd range, line pointer)
 * 2. Get or create buffer for this fd
 * 3. Loop until delimiter found or EOF:
 *    a. Search for delimiter in existing buffer data
 *    b. If found: extract line, shift remainder, return success
 *    c. If EOF and data remains: return remaining as final line
 *    d. If EOF and no data: return EOF status
 *    e. Read more data into buffer
 *
 * Return: GNL_LINE_READ (1), GNL_EOF (0), or GNL_ERROR (-1)
 */
int	get_next_line_delim(int fd, char **line, char delim)
{
	t_gnl_buffer	*buf;
	ssize_t			delim_pos;
	ssize_t			bytes_read;

	if (!line || fd < 0 || fd >= GNL_MAX_FD)
		return (GNL_ERROR);
	*line = NULL;
	buf = gnl_get_buffer(fd);
	if (!buf)
		return (GNL_ERROR);
	while (1)
	{
		delim_pos = gnl_find_delim(buf, delim);
		if (delim_pos >= 0)
		{
			*line = gnl_extract_line(buf, delim_pos);
			return (*line ? GNL_LINE_READ : GNL_ERROR);
		}
		if (buf->eof_reached)
		{
			if (buf->len > 0)
			{
				*line = gnl_extract_line(buf, buf->len - 1);
				return (*line ? GNL_LINE_READ : GNL_ERROR);
			}
			return (GNL_EOF);
		}
		bytes_read = gnl_fill_buffer(fd, buf);
		if (bytes_read < 0)
			return (GNL_ERROR);
	}
}

/**
 * get_next_line - Read next newline-delimited line from fd
 * @fd:   File descriptor to read from
 * @line: Pointer to store allocated line (caller must free)
 *
 * Convenience wrapper around get_next_line_delim with '\n' delimiter.
 *
 * Return: GNL_LINE_READ (1), GNL_EOF (0), or GNL_ERROR (-1)
 */
int	get_next_line(int fd, char **line)
{
	return (get_next_line_delim(fd, line, GNL_DEFAULT_DELIM));
}

/**
 * gnl_close - Release resources for a specific file descriptor
 * @fd: File descriptor to clean up
 *
 * Frees the buffer data and structure for this fd.
 * Safe to call multiple times or on uninitialized fd.
 * Should be called before close(fd) to prevent memory leaks.
 */
void	gnl_close(int fd)
{
	if (fd < 0 || fd >= GNL_MAX_FD)
		return ;
	if (g_buffers[fd])
	{
		free(g_buffers[fd]->data);
		free(g_buffers[fd]);
		g_buffers[fd] = NULL;
	}
}

/**
 * gnl_cleanup_all - Release all GNL resources
 *
 * Iterates through all possible file descriptors and frees their buffers.
 * Call at program exit or when resetting state completely.
 */
void	gnl_cleanup_all(void)
{
	int	i;

	i = 0;
	while (i < GNL_MAX_FD)
	{
		gnl_close(i);
		i++;
	}
}
