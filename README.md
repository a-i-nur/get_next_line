*This project has been created as part of the 42 curriculum by aakhmeto.*

# get_next_line

`get_next_line` is a 42 Common Core project focused on file-descriptor I/O and static state management.

- Author / Intra: `aakhmeto`

## Description

The goal is to implement:

```c
char	*get_next_line(int fd);
```

`get_next_line()` returns one line per call from a given file descriptor:

- returns a heap-allocated line including `\n` when present
- returns the last line without `\n` if EOF is reached
- returns `NULL` on EOF with no remaining data or on error

The implementation must work with regular files and standard input.

## Subject Requirements

| Item | Requirement |
|---|---|
| Function name | `get_next_line` |
| Prototype | `char *get_next_line(int fd);` |
| Mandatory files | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| External functions | `read`, `malloc`, `free` |
| Forbidden | `libft`, `lseek`, global variables |
| Buffer config | compile with `-D BUFFER_SIZE=n` (must also work without the flag using default value) |

## Instructions

Compile mandatory part (example with `BUFFER_SIZE=42`):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Compile mandatory part without explicit buffer define (uses default from header):

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

Compile bonus (multiple file descriptors):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

Minimal usage example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("input.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Algorithm and Data Structure Choices

The implementation uses incremental reading and persistent leftover state.

Algorithm overview:

1. Keep a static read buffer state across calls.
2. Before a new `read()`, consume any leftover unread bytes from the previous call.
3. Append characters to a dynamically growing output line until `\n` or EOF.
4. Stop immediately once a full line is formed (do not read the entire file).
5. Preserve post-`\n` bytes as tail data for the next call.

Data structures used:

- `t_read_buffer`
- `read_text[BUFFER_SIZE + 1]`: temporary chunk from `read()`
- `read_bytes`: number of bytes actually read
- `index_tail`: current unread position inside `read_text`
- `f_end_line`: line-complete flag
- `t_ret_line`
- `res`: dynamically allocated output string
- `len`: current length
- `size`: current capacity

Why this design:

- Static buffer state is required to continue reading exactly where the previous call stopped.
- Splitting read-state and output-state keeps logic predictable and easier to debug.
- Manual realloc strategy in `ft_line_realloc` avoids fixed-size output limits.
- Newline detection and tail tracking (`ft_check_end_line`) prevent over-reading and match subject constraints.

## Bonus

Bonus files are included:

- `get_next_line_bonus.c`
- `get_next_line_bonus.h`
- `get_next_line_utils_bonus.c`

Current bonus behavior:

- Supports multiple file descriptors simultaneously using per-fd static state (`buf[1024]`).

## Project Structure

- Mandatory header: `get_next_line.h`
- Mandatory sources: `get_next_line.c`, `get_next_line_utils.c`
- Bonus header: `get_next_line_bonus.h`
- Bonus sources: `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`
- Subject: `gnl_subject.pdf`

## Skills Developed in This Project

- static storage duration and stateful function design in C
- file descriptor I/O with `read()`
- dynamic memory growth and lifetime management per returned line
- EOF/error edge-case handling without memory leaks
- separation of mandatory/bonus implementations under 42 constraints

## Key Achievements

- Implemented line-by-line reading API compatible with 42 subject behavior.
- Implemented newline-aware stopping and tail preservation between calls.
- Added bonus support for interleaved reads from multiple file descriptors.
- Kept implementation independent from `libft`, as required.

## How This Maps to Real-World Engineering

- **Streaming parsers:** same pattern as log readers and protocol line parsers.
- **Stateful APIs:** static carry-over state mirrors iterator-like interfaces.
- **Memory discipline:** controlled allocation/reallocation is core in systems code.
- **I/O robustness:** explicit error and EOF handling is critical for reliable tooling.

## Resources

Classic references:

- `read(2)`: https://man7.org/linux/man-pages/man2/read.2.html
- `open(2)`: https://man7.org/linux/man-pages/man2/open.2.html
- `free(3)`: https://man7.org/linux/man-pages/man3/free.3p.html
- 42 subject PDF: `gnl_subject.pdf`
