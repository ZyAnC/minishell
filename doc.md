# minishell

# signal

WIFSIGNALED(status): Nonzero if STATUS indicates termination by a signal.

WTERMSIG(status): Get the signal number if the system is terminated by a

				  siganl.

WIFEXITED(status): Nonzero if STATUS indicates normal termination.

WEXITSTATUS(status): Get the exit status number if it is a normal

					 termination.


# Process exit status

1. Exit Status Range:

	- In Unix-like systems, the exit status of a process is    typically an 8-bit value, which means it can range from 0 to 255.
	- By using the range 0-127 for normal exit statuses and 128-255 for signal-induced terminations, the system can distinguish between normal exits and those caused by signals.

2. Normal Exit Status:

	- When a program terminates normally (for example, it completes its execution successfully), it returns an exit status of 0 (or any other value from 1 to 127) to indicate success or different types of errors.

	- These values represent the successful completion of the program and the return codes defined by the programmer.

3. Signal-Induced Termination:

	- When a process is terminated by a signal (such as SIGINT for interrupt, SIGTERM for termination, or SIGKILL for force termination), the exit status is calculated as 128 + signal number.

	- For example, if a process is terminated by SIGINT, which has a signal number of 2, the exit status would be 128 + 2 = 130.

	- The number 128 is a base value that serves to shift the range of exit statuses for signal-induced terminations.
