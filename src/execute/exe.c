/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/11 12:46:39 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

static inline void	ft_execve_failed(char **shellcmd, char *path)
{
	char	*message;
	if (!access(shellcmd[0], F_OK) && !access(shellcmd[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(shellcmd[0], '/'))
			ex_error(shellcmd[0],DIRECTORY,126);
		else
			ex_error(shellcmd[0],COMMAND,127);
	}
	message = ft_strjoin(shellcmd[0]," : ");
	ex_error(message,ERR,1);
	free(message);
	if (path)
		free(path);
}

int		builtin(char **cmd)
{
	int	size;

	size = ft_strlen(cmd[0]);
	if (!ft_strncmp(cmd[0], "env",size))
		return(ft_env());
	else if (!ft_strncmp(cmd[0], "cd",size))
		return(ft_cd(cmd));
	else if (!ft_strncmp(cmd[0], "echo",size))
		return(ft_echo(cmd));
	else if (!ft_strncmp(cmd[0], "pwd",size))
	{
		ft_printf("%s\n",getcwd(NULL,2048));
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "unset",size))
		return(ft_unset(cmd));
	else if (!ft_strncmp(cmd[0], "export",size))
		return(ft_export(cmd));
	else if (!ft_strncmp(cmd[0], "exit",size))
		ft_exit(cmd);
	return(0);
}
void	real_execute(t_cmd *cm)
{
	char	*path;

	if(!builtin(cm->cmd))
	{
		path = findvalidcmd(cm->cmd);
		if (!path)
			ex_error(cm->cmd[0],COMMAND,127);
		execve(path, cm->cmd, ms()->env);
		ft_execve_failed(cm->cmd, path);
	}
	exit(0);

}

void	free_cm(t_cmd *cm)
{
	t_cmd *current = cm;
	t_cmd *next_node;

	while (current != NULL)
	{
		next_node = current->next; // Store next node
		// Free the command array
		if (current->cmd != NULL)
			pp_free(cm->cmd);
		// Free input and output file names
		free(current->infile);
		free(current->outfile);
		free(current); // Free the current node
		current = next_node; // Move to the next node
	}
}

void exe(t_cmd *cm)
{
	pid_t	pipeid;
	int		prev_fd;

	prev_fd = -1;
	while (cm)
	{
		set_fd(cm);
		if(cm->herenum > 0)
			type_hdoc(cm);
		if (cm->outype == TK_PIPE)
			pipeid = type_outpipe(cm,&prev_fd);
		else if((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
		&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE))
			pipeid = exe_pipe2(cm);
		else if (cm->intype == TK_PIPE && (cm->outype == TK_OUT_RE
		|| cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			pipeid = exe_pipe3(cm);
			close(ms()->fd[0]);
		}
		cm = cm->next;
	}

	close_all(prev_fd);
	while (wait(NULL) > 0);
}

/*
t_cmd *create_node( t_token_type intype, t_token_type outype) {
	t_cmd *new_node = malloc(sizeof(t_cmd));
	if (!new_node) {
		perror("Failed to allocate memory");
		return NULL;
	}

	new_node->cmd = NULL;


	new_node->intype = intype;
	new_node->outype = outype;

	new_node->next = NULL;

	return new_node;
}
void	test()
{
	t_cmd *head = create_node(TK_NONE, TK_NONE);

	t_cmd *second = create_node(TK_NONE,TK_NONE);


t_cmd *third = create_node(TK_PIPE,TK_NONE);
		head->next = second;
		//second->next = third;
	char *str[] = {"env",NULL};
	char *str2[] = {"echo","1",NULL};
	char *str3[] = {NULL};
	char *file[] = {NULL};
	char *file2[] = {NULL,NULL};
	char *file3[] = {NULL,NULL};

		head->cmd=str;
		head->outfile = file;
		head->of = NULL;
		head->ofnum = 0;
		head->inf = "3";
		head->ifnum = 0;
	second->ifnum = 0;
	second->ofnum =0;
		second->cmd=str2;
		second->outfile = file2;

		third->cmd = str3;
		third->outfile = file3;
		third->ofnum = 0;
		third->ifnum = 0;
		third->inf = 0;

		char *infile3[] = {"9","10","8",NULL};
	char *infile[] = {"1","2","3",NULL};
	head->limiter = infile;
	head->herenum = 0;
	second->limiter = infile;
	second->herenum = 0;
		head->infile = infile;
			third->infile = infile3;

	exe(head);

}
*/
