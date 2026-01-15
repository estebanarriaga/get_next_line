# get_next_line

A robust, efficient line-reading library for C with multi-fd support and configurable delimiters.

## Table of Contents

- [Features](#features)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
- [Configuration](#configuration)
- [Examples](#examples)
- [Internal Design](#internal-design)
- [Building](#building)
- [Memory Management](#memory-management)

---

## Features

- **Multi-FD Support**: Read from multiple file descriptors simultaneously without losing state
- **Configurable Delimiter**: Support for any single-byte delimiter (newline, comma, custom)
- **Efficient Memory**: Intelligent buffer management using `realloc` and `memmove`
- **glibc Optimized**: Leverages SIMD-optimized functions (`memchr`, `memcpy`, `memmove`)
- **Clean API**: Clear return codes (success, EOF, error) for robust error handling
- **Zero Dependencies**: Only requires standard C library

---

## Quick Start

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     status;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((status = get_next_line(fd, &line)) == GNL_LINE_READ)
    {
        printf("%s", line);
        free(line);
    }

    gnl_close(fd);
    close(fd);
    return (status == GNL_EOF ? 0 : 1);
}
```

### Compilation

```bash
gcc -o reader main.c get_next_line.c
```

---

## API Reference

### Core Functions

#### `int get_next_line(int fd, char **line)`

Read the next newline-delimited line from a file descriptor.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fd` | `int` | File descriptor to read from |
| `line` | `char **` | Pointer to store allocated line (caller must free) |

**Returns:**
| Value | Constant | Meaning |
|-------|----------|---------|
| `1` | `GNL_LINE_READ` | Line successfully read |
| `0` | `GNL_EOF` | End of file reached |
| `-1` | `GNL_ERROR` | Error occurred |

**Notes:**
- Line includes the delimiter (`\n`) unless at EOF without trailing newline
- Caller is responsible for freeing `*line` after use
- Returns `GNL_ERROR` if `fd < 0`, `fd >= GNL_MAX_FD`, or `line` is NULL

---

#### `int get_next_line_delim(int fd, char **line, char delim)`

Read the next segment from a file descriptor using a custom delimiter.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fd` | `int` | File descriptor to read from |
| `line` | `char **` | Pointer to store allocated line (caller must free) |
| `delim` | `char` | Delimiter character to split on |

**Returns:** Same as `get_next_line()`

**Use Cases:**
- CSV parsing: `delim = ','` or `delim = ';'`
- Log files: `delim = '\n'` or custom record separator
- Binary protocols: `delim = '\0'` for null-terminated records

---

### Resource Management

#### `void gnl_close(int fd)`

Release all resources associated with a specific file descriptor.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fd` | `int` | File descriptor to clean up |

**Notes:**
- Call this when done reading from `fd` (before `close()`)
- Safe to call multiple times or on uninitialized fd
- Prevents memory leaks

---

#### `void gnl_cleanup_all(void)`

Release all GNL resources for all file descriptors.

**Use Cases:**
- Program exit cleanup
- Resetting state completely
- Memory leak prevention in long-running processes

---

## Configuration

Override defaults at compile time using `-D` flags:

### `GNL_BUFFER_SIZE`

Size of read buffer in bytes.

```bash
gcc -DGNL_BUFFER_SIZE=8192 ...
```

| Value | Use Case |
|-------|----------|
| `256` | Memory-constrained environments |
| `4096` (default) | General purpose |
| `65536` | High-throughput file reading |

### `GNL_MAX_FD`

Maximum number of file descriptors to track simultaneously.

```bash
gcc -DGNL_MAX_FD=2048 ...
```

| Value | Memory Usage |
|-------|--------------|
| `256` | 2 KB (pointers only) |
| `1024` (default) | 8 KB |
| `4096` | 32 KB |

### `GNL_DEFAULT_DELIM`

Default delimiter for `get_next_line()`.

```bash
gcc -DGNL_DEFAULT_DELIM='\0' ...
```

---

## Examples

### Reading a Text File

```c
int fd = open("data.txt", O_RDONLY);
char *line;

while (get_next_line(fd, &line) == GNL_LINE_READ)
{
    process_line(line);
    free(line);
}
gnl_close(fd);
close(fd);
```

### CSV Parsing

```c
int fd = open("data.csv", O_RDONLY);
char *field;

while (get_next_line_delim(fd, &field, ',') == GNL_LINE_READ)
{
    // field contains one CSV field (including trailing comma or newline)
    process_field(field);
    free(field);
}
gnl_close(fd);
close(fd);
```

### Multiple Files Simultaneously

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
char *line1, *line2;

// Read alternately from both files
get_next_line(fd1, &line1);  // First line from file1
get_next_line(fd2, &line2);  // First line from file2
get_next_line(fd1, &line1);  // Second line from file1 (state preserved!)

// Cleanup
gnl_close(fd1);
gnl_close(fd2);
close(fd1);
close(fd2);
```

### Reading from stdin

```c
char *line;

printf("Enter text (Ctrl+D to end):\n");
while (get_next_line(STDIN_FILENO, &line) == GNL_LINE_READ)
{
    printf("You entered: %s", line);
    free(line);
}
gnl_close(STDIN_FILENO);
```

### Reading from a Socket

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// ... connect to server ...

char *response;
while (get_next_line(sockfd, &response) == GNL_LINE_READ)
{
    handle_server_response(response);
    free(response);
}
gnl_close(sockfd);
close(sockfd);
```

### Error Handling

```c
int fd = open("file.txt", O_RDONLY);
char *line;
int status;

if (fd < 0)
{
    perror("open");
    return (1);
}

while ((status = get_next_line(fd, &line)) == GNL_LINE_READ)
{
    printf("%s", line);
    free(line);
}

if (status == GNL_ERROR)
{
    fprintf(stderr, "Error reading file\n");
    gnl_close(fd);
    close(fd);
    return (1);
}

// status == GNL_EOF: normal end of file
gnl_close(fd);
close(fd);
return (0);
```

---

## Internal Design

### Architecture Overview

```
                    +------------------+
                    |  get_next_line() |
                    +--------+---------+
                             |
                             v
                    +------------------+
                    | get_next_line_   |
                    |     delim()      |
                    +--------+---------+
                             |
              +--------------+--------------+
              |              |              |
              v              v              v
     +----------------+ +----------+ +-------------+
     |gnl_get_buffer()| |gnl_find_ | |gnl_extract_ |
     |                | | delim()  | |   line()    |
     +----------------+ +----------+ +-------------+
              |
              v
     +------------------+
     |gnl_fill_buffer() |
     +------------------+
              |
              v
     +------------------+
     |gnl_ensure_       |
     |   capacity()     |
     +------------------+
```

### Data Structures

#### Per-FD Buffer (`t_gnl_buffer`)

```c
typedef struct s_gnl_buffer
{
    char    *data;        // Dynamic buffer (heap allocated)
    size_t  size;         // Allocated capacity
    size_t  len;          // Bytes currently stored
    int     eof_reached;  // EOF flag
}   t_gnl_buffer;
```

#### Global State

```c
static t_gnl_buffer *g_buffers[GNL_MAX_FD];
```

- Array indexed by file descriptor
- O(1) lookup time
- Lazy allocation (buffer created on first read)
- NULL indicates unused slot

### Algorithm

1. **Validate inputs**: Check fd range and line pointer
2. **Get/create buffer**: Lazy allocation for this fd
3. **Main loop**:
   - Search for delimiter using `memchr()` (SIMD optimized)
   - If found: extract line with `memcpy()`, shift remainder with `memmove()`
   - If EOF reached: return remaining data or EOF status
   - Otherwise: grow buffer with `realloc()` if needed, `read()` more data
4. **Return**: Line pointer and status code

### Memory Strategy

| Operation | Old Implementation | New Implementation |
|-----------|-------------------|-------------------|
| Find delimiter | Loop character-by-character | `memchr()` (SIMD) |
| Concatenate | malloc + copy + free | `realloc()` (may extend in-place) |
| Extract line | malloc + copy | malloc + `memcpy()` |
| Remove line | malloc + copy + free | `memmove()` (in-place) |

**Result**: Fewer allocations, better cache utilization, vectorized operations.

### Buffer Growth Strategy

```
Initial size: GNL_BUFFER_SIZE (default 4096)
Growth: Double capacity when needed
```

This exponential growth minimizes reallocations for long lines while keeping memory usage reasonable.

---

## Building

### Simple Compilation

```bash
gcc -Wall -Wextra -Werror -o program main.c get_next_line.c
```

### With Custom Buffer Size

```bash
gcc -Wall -Wextra -Werror -DGNL_BUFFER_SIZE=8192 -o program main.c get_next_line.c
```

### As a Static Library

```bash
# Compile object file
gcc -Wall -Wextra -Werror -c get_next_line.c -o get_next_line.o

# Create archive
ar rcs libgnl.a get_next_line.o

# Link with your program
gcc -Wall -Wextra -Werror -o program main.c -L. -lgnl
```

### Debug Build

```bash
gcc -Wall -Wextra -Werror -g -fsanitize=address -o program main.c get_next_line.c
```

---

## Memory Management

### Caller Responsibilities

1. **Free returned lines**: Every successful call returns allocated memory
2. **Call `gnl_close(fd)`**: Before closing the file descriptor
3. **Call `gnl_cleanup_all()`**: At program exit (optional but recommended)

### Memory Leak Prevention

```c
// CORRECT: Free after use
while (get_next_line(fd, &line) == GNL_LINE_READ)
{
    process(line);
    free(line);  // Required!
}
gnl_close(fd);   // Required!

// INCORRECT: Memory leak
while (get_next_line(fd, &line) == GNL_LINE_READ)
{
    process(line);
    // Missing free(line) - LEAK!
}
// Missing gnl_close(fd) - LEAK!
```

### Valgrind Testing

```bash
gcc -g -o program main.c get_next_line.c
valgrind --leak-check=full ./program
```

Expected output with proper cleanup:
```
All heap blocks were freed -- no leaks are possible
```

---

## Thread Safety

**Current status**: Not thread-safe.

The global `g_buffers` array is shared across threads. For multi-threaded use:

1. Use one fd per thread (no shared fds)
2. Add mutex protection around `get_next_line()` calls
3. Consider a thread-local version (compile with `-DGNL_THREAD_LOCAL`)

---

## License

MIT License - See LICENSE file for details.
