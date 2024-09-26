/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:49:16 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/26 17:56:55 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"



pid_t exe_pipe(t_cmd *cm)
{
	pid_t	pid;
	int		i;
	int		fd;
	pid = fork();
 	if (pid == -1)
		ex_error("Fork", FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		i = 0;
		while(i < cm->ifnum - 1)
		{
			fd = open(cm->infile[i++], O_RDONLY , 0444);
			if (fd == -1)
			{
				if (!access(cm->inf, F_OK))
					ex_error(cm->inf, PREMISSON, 126);
				else
					ex_error(cm->inf,NFILE,2);
				restart(true);
			}
			close(fd);
		}
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
		dup2(ms()->in_fd,STDIN_FILENO);
		dup2(ms()->out_fd,STDOUT_FILENO);
		if (ms()->in_fd != 0)
			close(ms()->in_fd);
		if (ms()->out_fd != 1)
			close(ms()->out_fd);
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
