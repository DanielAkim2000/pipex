*This project has been created as part of the 42 curriculum by demane.*

# pipex

## Description

**pipex** is a 42 school project that recreates the behavior of shell pipelines in C. The goal is to understand how Unix processes communicate through pipes, how file descriptors are redirected, and how commands are located and executed via `PATH`.

In its mandatory part, the program mimics the following shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

It creates a pipe between two child processes: the first reads from `infile` and runs `cmd1`, the second runs `cmd2` and writes to `outfile`.

The bonus part extends this behavior to:

- **Multiple pipes** — an arbitrary number of commands chained together (`cmd1 | cmd2 | ... | cmdN`)
- **here_doc** — support for a heredoc-style input (`<<`), similar to:

```bash
cmd << LIMITER | cmd1 | ... | cmdN >> outfile
```

### Overview

| Component | Role |
|-----------|------|
| `main_mandatory.c` / `main_bonus.c` | Program entry points |
| `init.c` / `parse.c` | Initialization and command parsing |
| `path.c` | Resolve executables via `PATH` |
| `process.c` / `exec.c` | Fork, pipe, redirect, and execute |
| `here_doc.c` | Heredoc input handling (bonus) |
| `error.c` / `free.c` / `utils.c` | Error handling, cleanup, helpers |
| `gnl.c` / `gnl_utils.c` | `get_next_line` for heredoc reading |
| `libft/` | Custom C utility library |

---

## Instructions

### Requirements

- A Unix-like system (Linux / macOS)
- `cc` (or equivalent C compiler)
- `make`

### Compilation

Build the mandatory version:

```bash
make
```

Build the bonus version (multiple pipes + here_doc):

```bash
make bonus
```

Other useful targets:

```bash
make clean      # remove object files
make fclean     # remove object files and the binary
make re         # fclean then rebuild mandatory
make rebonus    # fclean then rebuild bonus
```

The resulting executable is named `pipex`. Compiling with `make` or `make bonus` also builds `libft` automatically.

### Execution

**Mandatory** (exactly 4 arguments after the program name):

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Equivalent to:

```bash
< infile cmd1 | cmd2 > outfile
```

**Bonus — multiple commands:**

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```

**Bonus — here_doc:**

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" ... "cmdN" outfile
```

Equivalent to:

```bash
cmd << LIMITER | cmd1 | ... | cmdN >> outfile
```

### Usage examples

```bash
# Sort unique lines from infile into outfile
./pipex infile "cat" "wc -l" outfile

# Filter then count
./pipex infile "grep hello" "wc -w" outfile

# Bonus: three commands
./pipex infile "cat" "grep a" "wc -l" outfile

# Bonus: here_doc
./pipex here_doc END "cat" "wc -l" outfile
# then type lines, finish with END
```

---

## Library

This project uses **libft**, a custom C library developed as part of the 42 curriculum and reused across projects.

`libft` provides a set of reimplemented standard C library functions and additional helpers needed by pipex (string splitting, memory allocation, file descriptor output, linked lists, etc.). It is compiled as a static archive (`libft/libft.a`) and linked with the pipex binary.

### Main categories

| Category | Examples |
|----------|----------|
| Character checks | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint` |
| Memory | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_calloc` |
| Strings | `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strdup`, `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_strncmp` |
| Conversion | `ft_atoi`, `ft_itoa`, `ft_atol` |
| Output | `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` |
| Linked lists | `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstclear`, `ft_lstmap`, … |
| Extra helpers | `ft_strjoin_sep`, `ft_str_is_space`, `ft_maxint`, `ft_minint`, `ft_has_duplicates` |

In pipex, libft is especially used for:

- parsing command lines (`ft_split`, string helpers)
- building full executable paths (`ft_strjoin`, `ft_strjoin_sep`)
- writing error messages (`ft_putstr_fd`)
- allocating and freeing memory safely

The library sources live in `libft/` and are built via `libft/Makefile`.

---

## Features

- Recreation of `< infile cmd1 | cmd2 > outfile`
- Correct handling of pipes and file descriptor redirections
- Command resolution through the `PATH` environment variable
- Proper process management with `fork`, `execve`, and `wait`
- Error handling consistent with shell-like behavior (e.g. missing infile, command not found)
- **Bonus:** unlimited number of chained commands
- **Bonus:** `here_doc` support with append mode on the outfile

---

## Technical choices

- Separate entry points for mandatory (`main_mandatory.c`) and bonus (`main_bonus.c`), sharing the same core modules
- A central `t_pipex` structure holding file descriptors, parsed commands, PIDs, and state
- Child processes handle redirections and execution; the parent orchestrates pipes and waits for children
- `get_next_line` is used to read heredoc input line by line until the limiter
- Static linking against `libft` to keep the project self-contained

---

## Resources

### Documentation & references

- [pipe(2) — Linux man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [fork(2) — Linux man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2) — Linux man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup2(2) — Linux man page](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [wait(2) / waitpid(2) — Linux man page](https://man7.org/linux/man-pages/man2/wait.2.html)
- [access(2) — Linux man page](https://man7.org/linux/man-pages/man2/access.2.html)
- [GNU Bash Reference Manual — Pipelines](https://www.gnu.org/software/bash/manual/html_node/Pipelines.html)
- [The Linux Programming Interface (Michael Kerrisk)](https://man7.org/tlpi/) — chapters on processes, pipes, and file descriptors

### AI usage

AI assistance (Cursor) was used for the following tasks:

- **README** — drafting and structuring this `README.md` to meet the Chapter V requirements (description, instructions, library section, resources)
- **Debugging support** — discussing error-handling priorities, `here_doc` edge cases, and wait/exit status behavior during development
- **Code review / explanation** — clarifying Unix concepts (`pipe`, `fork`, `dup2`, `execve`) and reviewing logic around process orchestration

AI was **not** used to generate the full project from scratch: core design, implementation, and testing were done by the student. AI output was reviewed and adapted before inclusion.
