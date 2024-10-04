

#include "minishell.h"

pid_t exe_pipe(t_cmd *cm)
{
	pid_t	pid;

	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		check_infile(cm);
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->fd[1],STDOUT_FILENO);
		close(ms()->fd[0]);
		close(ms()->fd[1]);
		real_execute(cm);
	}

	return(pid);
}
pid_t exe_pipe2(t_cmd *cm)
{
	pid_t	pid;

	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		if (cm->intype == TK_HDOC)
			cm->ifnum++;
		check_infile(cm);
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);
		close_inout();
		real_execute(cm);
	}
	return(pid);
}

pid_t exe_pipe3(t_cmd *cm)
{
	pid_t	pid;
	int		i;

	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		i = 0;
		while(i < cm->ofnum - 1)
			close(open(cm->outfile[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644));
		dup2(ms()->fd[0],STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);
		close(ms()->fd[1]);
		close(ms()->fd[0]);
		real_execute(cm);
	}
	return(pid);
}
