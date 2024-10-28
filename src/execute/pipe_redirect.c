

#include "minishell.h"

pid_t exe_pipe(t_cmd *cm)
{
	pid_t	pid;

	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();
		if(ms()->in_fd == -1)
			exit(ms()->exit);
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
	int status;

	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();


		if (cm->intype == TK_HDOC)
			cm->ifnum++;
		check_infile(cm);

		if(ms()->in_fd == -1)
			exit(ms()->exit);
		if(dup2(ms()->out_fd,STDOUT_FILENO) == -1 || dup2(ms()->in_fd,STDIN_FILENO) == -1)
		{
			close_inout();
			exit(1);
		}
		close_inout();
		real_execute(cm);
	}
	waitpid(pid,&status,0);
	ms()->exit = WEXITSTATUS(status);
	return(pid);
}

pid_t exe_pipe3(t_cmd *cm)
{
	pid_t	pid;

	int status;

	signal_ignore();
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		signal_child();


		dup2(ms()->fd[0],STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);
		if(dup2(ms()->out_fd,STDOUT_FILENO) == -1)
		{
			close(ms()->fd[1]);
			close(ms()->fd[0]);
			exit(1);
		}
		close(ms()->fd[1]);
		close(ms()->fd[0]);
		real_execute(cm);
	}
	waitpid(pid,&status,0);
	ms()->exit = WEXITSTATUS(status);
	return(pid);

}
