/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earriaga <earriaga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:48:28 by earriaga          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by earriaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>

/* Return Codes */
# define GNL_LINE_READ   1    /* Successfully read a line */
# define GNL_EOF         0    /* End of file reached */
# define GNL_ERROR      -1    /* Error occurred */

/* Configuration Macros (override at compile time with -D flag) */
# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 4096
# endif

# ifndef GNL_MAX_FD
#  define GNL_MAX_FD 1024
# endif

# ifndef GNL_DEFAULT_DELIM
#  define GNL_DEFAULT_DELIM '\n'
# endif

/* Data Structures */

/**
 * t_gnl_buffer - Per-fd state buffer for tracking read progress
 * @data:        Dynamic buffer holding unprocessed data
 * @size:        Current allocated size of data buffer
 * @len:         Actual bytes stored in buffer
 * @eof_reached: Flag indicating EOF encountered on this fd
 *
 * Each file descriptor maintains its own buffer to support
 * reading from multiple files simultaneously.
 */
typedef struct s_gnl_buffer
{
	char	*data;
	size_t	size;
	size_t	len;
	int		eof_reached;
}	t_gnl_buffer;

/**
 * get_next_line - Read next newline-delimited line from fd
 * @fd:   File descriptor to read from
 * @line: Pointer to store the allocated line (caller must free)
 *
 * Return: GNL_LINE_READ (1) on success, GNL_EOF (0) at end of file,
 *         GNL_ERROR (-1) on error
 *
 * Note: Line includes the delimiter unless at EOF without trailing delimiter.
 *       Caller is responsible for freeing *line after use.
 */
int		get_next_line(int fd, char **line);

/**
 * get_next_line_delim - Read next delimited segment from fd
 * @fd:    File descriptor to read from
 * @line:  Pointer to store the allocated line (caller must free)
 * @delim: Delimiter character to split on
 *
 * Return: GNL_LINE_READ (1) on success, GNL_EOF (0) at end of file,
 *         GNL_ERROR (-1) on error
 *
 * Note: Supports any single-byte delimiter (e.g., '\n', ',', '\0').
 *       For CSV: use ',' or ';' as delimiter.
 *       For log files: use '\n' or custom record separator.
 */
int		get_next_line_delim(int fd, char **line, char delim);

/**
 * gnl_close - Release all resources associated with a file descriptor
 * @fd: File descriptor to clean up
 *
 * Note: Call this when done reading from fd (before close()).
 *       Safe to call multiple times or on uninitialized fd.
 */
void	gnl_close(int fd);

/**
 * gnl_cleanup_all - Release all GNL resources (all file descriptors)
 *
 * Note: Call this at program exit or when resetting state.
 */
void	gnl_cleanup_all(void);

#endif
