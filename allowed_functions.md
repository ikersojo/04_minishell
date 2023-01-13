# Allowed Functions

## Readline related functions (NEW)
MAIN FUNCTION:
```c
#include <stdio.h>
char	*readline (const char *prompt);

DESCRIPTION:
readline will read a line from the terminal and return it. The line returned
is allocated with malloc(3); the caller must free it when finished. The line
returned has the final newline removed.
If prompt is NULL or the empty string, no prompt is issued.
NOTE: readline offers editing capabilities while the user is entering the line.

RETURN VALUE:
readline returns the text of the line read.
If an EOF is read with a non-empty line, it is treated as a newline.
A blank line returns the empty string. If EOF is encountered while reading a line,
and the line is empty, NULL is returned.
```

AUX FUNCTIONS:
```c
void	rl_clear_history (void)

DESCRIPTION:
Clear the history list by deleting all of the entries.
```

```c
int	rl_on_new_line (void)

DESCRIPTION:
Tell the update functions that we have moved onto a new (empty) line, usually
after outputting a newline.
```

```c
void	rl_replace_line (const char *text, int clear_undo)

DESCRIPTION:
Replace the contents of rl_line_buffer with text. The point and mark are preserved,
if possible. If clear_undo is non-zero, the undo list associated with the current
line is cleared.
```

```c
void	rl_redisplay (void)

DESCRIPTION:
Change what’s displayed on the screen to reflect the current contents of
rl_line_buffer.
```

```c
void add_history (const char *string)

DESCRIPTION:
Place string at the end of the history list. The associated data field
(if any) is set to NULL.
```

## Functions related to text input/output
printf, write, open, read, close

## Functions related to memmory allocation
malloc, free

## Processes related functions
access:
```c
#include <unistd.h>
int	access(const char *pathname, int mode);

DESCRIPTION:
access() checks whether the calling process can access the file pathname.
The mode specifies the accessibility checks to be performed:
F_OK, R_OK, W_OK or X_OK

RETURN VALUE:
On success zero is returned: all requested permissions granted, or for
F_OK the file exists.
On error -1 is returned, and errno is set to indicate the error.
```
execve, dup, dup2, pipe,

exit
```c
#include <stdlib.h>
void	exit(int status);

DESCRIPTION:
The exit() function causes normal process termination. EXIT_SUCCESS and EXIT_FAILURE,
that may be passed to exit() to indicate successful or unsuccessful termination status.
```

perror:
```c
#include <string.h>
void perror(const char *s);

DESCRIPTION:
The perror() function produces a message on standard error describing the last error
encountered during a call to a system or library function. If s is not NULL the argument
string s is printed, followed by a colon and a blank.
```

strerror:
```c
#include <stdio.h>
char *strerror(int errnum);

DESCRIPTION:
The strerror() function returns a pointer to a string that describes the error code
passed in the argument errnum.
```

fork:
```c
#include <unistd.h>
pid_t	fork(void);

DESCRIPTION:
fork() creates a new process by duplicating the calling process.
The child process and the parent process run in separate memory spaces.
At the time of fork() both memory spaces have the same content. After fork,
modifications performed by one of the processes do not affect the other.

RETURN VALUE:
On success, the PID of the child process is returned in the parent, and 0 is
returned in the child. On failure, -1 is returned in the parent, no child
process is created, and errno is set to indicate the error.
```

wait, waitpid, wait3 and wait4:
```c
#include <sys/wait.h>
pid_t	wait(int *wstatus);
pid_t	waitpid(pid_t pid, int *wstatus, int options);
pid_t	wait3(int *status, int options, struct rusage *rusage);
pid_t	wait4(pid_t pid, int *status, int options, struct rusage *rusage);

DESCRIPTION:
All of these system calls are used to wait for state changes in a child of the
calling process, and obtain information about the child whose state has changed.
- wait() suspends execution of the calling thread until one of its children terminates.
   - wstatus: WIFEXITED:    returns true if the child terminated normally.
              WEXITSTATUS:  returns the exit status of the child (as the return statement).
                            This macro should only be employed if WIFEXITED returned true.
              WIFSIGNALED:  returns true if the child process was terminated by a signal.
              WTERMSIG:     returns the number of the signal that caused the child process to terminate.
                            This macro should only be employed if WIFSIGNALED returned true.
              WCOREDUMP:    returns true if the child produced a core dump.
                            This macro should only be employed if WIFSIGNALED returned true.
              WIFSTOPPED:   returns true if the child process was stopped by delivery of a signal.
              WSTOPSIG:     returns the number of the signal which caused the child to stop.
                            This macro should only be employed if WIFSTOPPED returned true.
              WIFCONTINUED: returns true if the child process was resumed by delivery of SIGCONT.
- waitpid() suspends execution of the calling thread until a child specified by pid argument
  has changed state:
   - pid: < -1 (wait for any child in PID group from abs(pid))
            -1 (wait for any child)
             0 (wait for any child in the same PID group as calling process)
           > 0 (wait for specified child)
   - options: The value of options is an OR of zero or more of the following constants:
              WNOHANG: return immediately if no child has exited.
              WUNTRACED: also return if a child has stopped.
              WCONTINUED: also return if a stopped child has been resumed by delivery of SIGCONT.
- wait3() and wait4() are similar to waitpid(), but additionally return resource usage
  information about the child in the structure pointed to by rusage. wait3() waits of any
  child, while wait4() can be used to select a specific child, or children, on which to wait.

RETURN VALUE:
On success, returns the process ID of the terminated child; on error, -1 is returned.
For waitpid, wait3 and wait4: if WNOHANG was specified and one or more child(ren) specified
by pid exist, but have not yet changed state, then 0 is returned.
```

unlink:
```c
#include <unistd.h>
int unlink(const char *pathname);

DESCRIPTION:
unlink() deletes a name from the file system. If that name was the last
link to a file and no processes have the file open the file is deleted
and the space it was using is made available for reuse.
If the name was the last link to a file but any processes still have the
file open the file will remain in existence until the last file descriptor
referring to it is closed.

If the name referred to a symbolic link the link is removed.

If the name referred to a socket, fifo or device the name for it is removed
but processes which have the object open may continue to use it.

RETURN VALUE:
On success, zero is returned. On error, -1 is returned, and errno is set.
```

## Functions related to signals

```c
#include <signal.h>
int	kill(pid_t pid, int sig);

DESCRIPTION:
The kill() system call can be used to send any signal to any process group or process. pid:
	< -1 (sig is sent to every process in the process group whose ID is -pid)
	  -1 (sig is sent to every process for which the calling process has permission to send signals)
	   0 (sig is sent to every process in the process group of the calling process)
	 > 0 (sig is sent to the process with the ID specified by pid)
If sig is 0, then no signal is sent, but existence and permission checks are still performed.

RETURN VALUE:
On success (at least one signal was sent), zero is returned.
On error, -1 is returned, and errno is set to indicate the error.
```

```c
WARNING: the behavior of signal() varies across UNIX versions, and has also varied historically
across different versions of Linux. Avoid its use: use sigaction(2) instead.

#include <signal.h>
int	sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);

DESCRIPTION:
The sigaction() system call is used to change the action taken by a process on receipt 
of a specific signal. signum specifies the signal and can be any valid signal except
SIGKILL and SIGSTOP. If act is non-NULL, the new action for signal signum is installed
from act.  If oldact is non-NULL, the previous action is saved in oldact.

RETURN VALUE:
0 on success; on error, -1 is returned, and errno is set to indicate the error.
```

## TTY related functions

```c
#include <unistd.h>
int	isatty(int fd);

DESCRIPTION:
The isatty() function tests whether fd is an open file descriptor
referring to a terminal.

RETURN VALUE:
isatty() returns 1 if fd is an open file descriptor referring to
a terminal; otherwise 0 is returned, and errno is set to indicate
the error.
```

```c
#include <unistd.h>
char	*ttyname(int fd);

DESCRIPTION / RETURN VALUE:
The function ttyname() returns a pointer to a pathname on success.
On error, NULL is returned, and errno is set to indicate the error.
```

```c
#include <unistd.h>
int	ttyslot(void);

DESCRIPTION / RETURN VALUE:
The legacy function ttyslot() returns the index of the current user's entry in some file.
?????
```

```c
#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...);

DESCRIPTION:
The ioctl() system call manipulates the terminals, addressed by their file descriptor.

RETURN VALUE:
Usually, on success zero is returned.  A few ioctl() requests use
the return value as an output parameter and return a nonnegative
value on success.  On error, -1 is returned, and errno is set to
indicate the error.
```

```c
#include <stdlib.h>
int ioctl(int fd, unsigned long request, ...);
char	*getenv(const char *name);

DESCRIPTION:
The getenv() function searches the environment list to find the environment
variable name, and returns a pointer to the corresponding value string.

RETURN VALUE:
The getenv() function returns a pointer to the value in the
environment, or NULL if there is no match.
```

```c
#include <unistd.h>
int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

DESCRIPTION:
The termios functions describe a general terminal interface that is provided
to control asynchronous communications ports.
```

```c
#include <term.h>
int tgetent(char *bp, const char *name);
int tgetflag(char *id);
int tgetnum(char *id);
char *tgetstr(char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));

DESCRIPTION:
These routines are included as a conversion aid for programs that use the termcap
library. Their parameters are the same and the routines are emulated using the
terminfo database. Thus, they can only be used to query the capabilities of entries
for which a terminfo entry has been compiled.

The tgetent routine loads the entry for name. It returns 1 on success, 0 if there
is no such entry, and -1 if the terminfo database could not be found. The emulation
ignores the buffer pointer bp.

The tgetflag routine gets the boolean entry for id, or zero if it is not available.

The tgetnum routine gets the numeric entry for id, or -1 if it is not available.

The tgetstr routine returns the string entry for id, or zero if it is not available.
Use tputs to output the returned string. The return value will also be copied to the
buffer pointed to by area, and the area value will be updated to point past the null
ending this value.

Only the first two characters of the id parameter of tgetflag, tgetnum and tgetstr are
compared in lookups.

The tgoto routine instantiates the parameters into the given capability. The output from
this routine is to be passed to tputs.

The tputs routine is described on the curs_terminfo(3X) manual page. It can retrieve
capabilities by either termcap or terminfo name.
```

## Directory related functions

getcwd:
```c
#include <unistd.h>
char *getcwd(char *buf, size_t size);

DESCRIPTION:
The getcwd() function copies an absolute pathname of the current
working directory to the array pointed to by buf, which is of
length size.

If the length of the absolute pathname of the current working
directory, including the terminating null byte, exceeds size
bytes, NULL is returned, and errno is set to ERANGE; an
application should check for this error, and allocate a larger
buffer if necessary

RETURN VALUE:
On success, these functions return a pointer to a string
containing the pathname of the current working directory.  In the
case of getcwd() and getwd() this is the same value as buf.

On failure, these functions return NUL.
```

chdir:
```c
#include <unistd.h>
int chdir(const char *path);

DESCRIPTION:
chdir() changes the current working directory of the calling
process to the directory specified in path.

RETURN VALUE:
On success, zero is returned.  On error, -1 is returned, and
errno is set to indicate the error.
```

stat, lstat and fstat
```c
#include <unistd.h>
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);

DESCRIPTION:
These functions return information about a file pointed to by
path and fills in buf.
lstat() is identical to stat(), except that if path is a symbolic
link, then the link itself is stat-ed, not the file that it refers to.
fstat() is identical to stat(), except that the file to be stat-ed is
specified by the file descriptor fd.

RETURN VALUE:
On success, zero is returned.  On error, -1 is returned, and
errno is set to indicate the error.
```

opendir, readdir, closedir,

```c
#include <dirent.h>
DIR *opendir(const char *name);

DESCRIPTION:
The function opens a directory stream corresponding to the directory name,
and returns a pointer to the directory stream. The stream is positioned at
the first entry in the directory.

RETURN VALUE:
On success, return a pointer to the directory stream.
On error, NULL is returned
```
```c
#include <dirent.h>
struct dirent *readdir(DIR *dirp);

DESCRIPTION:
The readdir() function returns a pointer to a dirent structure
representing the next directory entry in the directory stream
pointed to by dirp.  It returns NULL on reaching the end of the
directory stream or if an error occurred.

RETURN VALUE:
On success, readdir() returns a pointer to a dirent structure.
If the end of the directory stream is reached, NULL is returned
and errno is not changed.  If an error occurs, NULL is returned
and errno is set to indicate the error.  To distinguish end of
stream from an error, set errno to zero before calling readdir()
and then check the value of errno if NULL is returned.
```

```c
#include <dirent.h>
int closedir(DIR *dirp);

DESCRIPTION:
The closedir() function closes the directory stream associated
with dirp.  A successful call to closedir() also chagoloses the
underlying file descriptor associated with dirp.  The directory
stream descriptor dirp is not available after this call.

RETURN VALUE:
The closedir() function returns 0 on success.  On error, -1 is
returned, and errno is set to indicate the error.
```
