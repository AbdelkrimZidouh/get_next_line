_This project has been created as part of the 42 curriculum by azidouh._

# get_next_line

## Description

**get_next_line** is a C function that reads and returns a single line from a file descriptor. The project is a fundamental exercise in memory management, static variables, and file I/O operations in C.  The goal is to create a function that can read from any file descriptor (files, standard input, network sockets, etc.) one line at a time, regardless of the buffer size used for reading.

The function handles multiple edge cases including:
- Variable line lengths
- Files with or without trailing newlines
- Multiple file descriptors simultaneously (bonus part)
- Different buffer sizes (configurable at compilation)
- Memory leaks prevention

This project teaches crucial concepts such as static variables persistence across function calls, dynamic memory allocation, and efficient buffer management. 

## Instructions

### Compilation

The project can be compiled with any C compiler. Here's how to compile it:

**Standard version (single file descriptor):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

**Bonus version (multiple file descriptors):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main. c -o gnl_bonus
```

The `BUFFER_SIZE` macro can be set to any positive value.  Common values are 1, 42, 1024, or 8192. Each value will affect performance differently: 
- Smaller values (1-10): More read() calls, slower but useful for testing
- Medium values (42-1024): Balanced performance
- Larger values (4096-8192): Fewer read() calls, better performance for large files

### Usage

Include the header file in your program:
```c
#include "get_next_line.h"
```

Function prototype:
```c
char *get_next_line(int fd);
```

**Basic example:**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free each line!
    }
    close(fd);
    return 0;
}
```

**Reading from standard input:**
```c
char *line;

while ((line = get_next_line(0)) != NULL)  // 0 = stdin
{
    printf("You entered: %s", line);
    free(line);
}
```

### Return Value

- Returns a line read from the file descriptor, including the terminating `\n` character (if present)
- Returns `NULL` when there's nothing left to read or if an error occurs
- The caller is responsible for freeing the returned string

## Algorithm Explanation and Justification

### Selected Algorithm:  Static Buffer with Progressive Reading

The algorithm chosen for this implementation uses a **static variable to maintain state between function calls**, combined with a **dynamic buffer allocation strategy**.  Here's the detailed breakdown:

#### Core Strategy

1. **Static Variable Persistence**: 
   - A static pointer `tmp` (or `tmp[OPEN_MAX]` for bonus) persists between function calls
   - This stores any excess data read beyond the current line
   - Eliminates the need to re-read data that was already fetched

2. **Read-Accumulate-Extract Pattern**:
   ```
   Step 1: Check if static buffer contains a complete line (\n found)
   Step 2: If not, read BUFFER_SIZE bytes from fd
   Step 3: Append new data to static buffer
   Step 4: Repeat until \n is found or EOF is reached
   Step 5: Extract one line and update static buffer with remaining data
   ```

#### Key Functions

**`get_next_line(int fd)`**: Main function that orchestrates the reading process
- Validates input (fd >= 0, BUFFER_SIZE > 0)
- Manages the read loop
- Returns one complete line

**`copy(char *tmp, char *buff)`**: Concatenates new data to existing buffer
- Efficiently joins the static buffer with newly read data
- Handles NULL cases (first read)
- Uses custom `ft_strjoin` implementation

**`get_line(char **tmp, ssize_t len)`**: Extracts a single line from buffer
- Searches for `\n` character
- Extracts substring up to and including `\n`
- Handles EOF without trailing newline
- Calls `ft_modify` to clean up the static buffer

**`ft_modify(char **tmp)`**: Updates the static buffer after line extraction
- Removes the returned line from static storage
- Keeps remaining data for next call
- Handles memory reallocation

#### Bonus Implementation:  Multiple File Descriptors

The bonus version uses an **array of static pointers** (`static char *tmp[OPEN_MAX]`) where:
- Each index corresponds to a file descriptor
- `OPEN_MAX` is typically 1024 (maximum number of open files)
- Each FD maintains its own independent buffer
- Allows interleaved reading from multiple files: 
  ```c
  get_next_line(fd1);  // Read line 1 from file 1
  get_next_line(fd2);  // Read line 1 from file 2
  get_next_line(fd1);  // Read line 2 from file 1
  ```

## Resources

### Documentation
- [Linux man pages - read(2)](https://man7.org/linux/man-pages/man2/read.2.html) - Documentation for the read() system call
- [Linux man pages - open(2)](https://man7.org/linux/man-pages/man2/open.2.html) - Documentation for file opening
- [Linux man pages - malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) - Dynamic memory allocation
- [C Static Variables](https://www.geeksforgeeks.org/static-variables-in-c/) - Understanding static variable scope and lifetime

### Articles & Tutorials
- [File I/O in C Programming](https://www.programiz.com/c-programming/c-file-input-output) - Basic concepts of file handling
- [Understanding File Descriptors](https://www.bottomupcs.com/file_descriptors.xhtml) - Deep dive into how file descriptors work
- [Memory Management in C](https://www.learn-c.org/en/Dynamic_allocation) - malloc, free, and memory leaks

### 42 Resources
- [42 Cursus - get_next_line subject](https://github.com/42School/norminette) - Official project subject
- 42 Peer evaluations and corrections

### AI Usage

AI assistance (GitHub Copilot and ChatGPT) was used in the following ways during this project: 

1. **Documentation and Learning**:
   - Understanding the mechanics of static variables and their persistence
   - Clarifying the behavior of read() with different buffer sizes
   - Learning about file descriptor management in Unix systems

2. **Code Review and Debugging**:
   - Identifying potential memory leaks using AI-powered analysis
   - Understanding segmentation faults and NULL pointer dereferences
   - Optimizing string manipulation functions

3. **Edge Case Discovery**:
   - AI helped identify edge cases such as: 
     - Files ending without a newline character
     - Empty files or empty lines
     - Very large files with small BUFFER_SIZE
     - Reading from stdin vs regular files

4. **Not Used For**:
   - Writing the core algorithm logic (entirely original work)
   - Copy-pasting complete function implementations
   - Solving the project without understanding the concepts

**Learning Outcome**: While AI tools were helpful for understanding concepts and debugging, the implementation itself was coded manually after fully understanding the requirements and algorithm design. This approach ensured deep learning of memory management and file I/O concepts.

---

**Note**: This implementation passes all 42 mandatory and bonus requirements, including norminette compliance, memory leak checks (valgrind), and edge case handling. 
