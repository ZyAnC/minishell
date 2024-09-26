/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/26 11:27:47 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./minishell.h"
void	pp_free(char **fly)
{
	int	j;

	j = 0;
	while (fly[j])
		free(fly[j++]);
	free(fly);
}

void	set_fd(t_cmd *cm)
{

	if(cm->prepipe == 1)
		ms()->in_fd = ms()->fd[0];
	if (cm->intype == TK_IN_RE)
		(ms()->in_fd) = open(cm->infile, O_RDONLY, 0444);
	//else if (cm->intype  == TK_HDOC)
	//	(ms()->in_fd) = heredoc(cm->infile);
	if (ms()->in_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (!access(cm->infile, F_OK))
			applyerror(); // permisson
		else
			applyerror(); // no such file
		restart(true);
	}
	else if (cm->outype  == TK_OUT_RE)
		(ms()->out_fd) = open(cm->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cm->outype == TK_APPEND)
		(ms()->out_fd) = open(cm->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cm->outype == TK_NONE)
		(ms()->out_fd) = STDOUT_FILENO;
	if (ms()->out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (!access(cm->infile, F_OK))
			applyerror(); // permisson
		else
			applyerror(); // no such file
		restart(true);
	}
}
void	ex_error(char *message, t_error type, int err_status)
{
	if(message)
		ft_putstr_fd(message, 2);
	if (type == DIRECTORY)
		ft_putstr_fd(": Is a directory", 2);
	if (type == COMMAND)
		ft_putstr_fd(": command not found", 2);
	if (type == NFILE)
		ft_putstr_fd(": No such file or directory", 2);
	if (type == ERR)
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	ms()->exit = err_status;
}


static inline char	*pathincmd(char **shellcmd)
{
	if (!access(shellcmd[0], F_OK))
		return (ft_strdup(shellcmd[0]));
	else
		ex_error(shellcmd[0],NFILE,127);
	return(NULL);
}

static inline char	*check_filename(char **filename, char **cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	while (filename[i])
	{
		path = ft_strjoin(filename[i++], "/");
		if (!path)
			return (0);
		full_path = ft_strjoin(path, cmd[0]);
		free(path);
		if (!full_path)
			return (0);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			pp_free(filename);
			return (full_path);
		}
		free(full_path);
	}
	pp_free(filename);
	return (0);
}

char	*findvalidcmd(char **shellcmd)
{
	char	**filename;

	if (ft_strchr(shellcmd[0], '/'))
		return (pathincmd(shellcmd));
	filename = ft_split(ms()->path + 5, ':');
	if (!filename)
		return (NULL);
	return (check_filename(filename, shellcmd));
}/*
static inline void	ft_execve_failed(char **shellcmd, char *path)
{
	if (!access(shellcmd[0], F_OK) && !access(shellcmd[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(shellcmd[0], '/'))
			ex_error(shellcmd[0],DIRECTORY,126);
		else
			ex_error(shellcmd[0],COMMAND,127);
	}
	ex_error(shellcmd[0],ERR,1);
	if (path)
		free(path);
}*/
void	real_execute(t_cmd *cm)
{
	char	*path;

	path = findvalidcmd(cm->cmd);
	if (!path)
		ex_error(cm->cmd[0],COMMAND,127);
	execve(path, cm->cmd, ms()->env);


	//ft_execve_failed(cm->cmd, path);

}
/*
	is_pipe means cmd before pipe ls -l |					exe_pipe
	is_pipe && prepipe mean cmd between 2 pipe | ls -l |	exe_pipe2
	prepipe means cmd behind pipe | ls -l					exe_pipe3

*/
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
void	exe(t_cmd *cm)
{

		pid_t pipeid;
		while (cm)
		{
			set_fd(cm);
			if (cm->ispipe == 1 && cm->prepipe == 0)
			{
					if(pipe(ms()->fd) == -1 )
						applyerror();
					pipeid = exe_pipe(cm);
					cm->next->prepipe = 1;
			}
		//else if (cm->outype == TK_PIPE && cm->prepipe == 1)
			//exe_pipe2(cm);
			else if (cm->ispipe != 1 && cm->prepipe == 1)
				pipeid = exe_pipe3(cm);
		//else if (cm->outype != TK_PIPE && cm->prepipe == 0)
			//exe_simple(cm);
			cm = cm->next;
		}
		if(ms()->in_fd != 0)
			close(ms()->in_fd);
		if(ms()->out_fd != 1)
			close(ms()->out_fd);
		close(ms()->fd[1]);
		close(ms()->fd[0]);
		waitpid(pipeid, NULL, 0);


	//free_cm(cm);
}


t_cmd *create_node(char *infile, char *outfile, t_token_type intype, t_token_type outype, int ispipe) {
	t_cmd *new_node = malloc(sizeof(t_cmd));
	if (!new_node) {
		perror("Failed to allocate memory");
		return NULL;
	}

	new_node->cmd = NULL;
	new_node->infile = infile;
	new_node->outfile = outfile;
	new_node->intype = intype;
	new_node->outype = outype;
	new_node->ispipe = ispipe;
	new_node->prepipe = 0;
	new_node->next = NULL;

	return new_node;
}
void	test()
{
	t_cmd *head = create_node(NULL, NULL, TK_NONE, TK_NONE, 1);

	t_cmd *second = create_node(NULL, "9", TK_NONE, TK_OUT_RE, 0);



		head->next = second;
	char *str[] = {"echo","asda",NULL};
	char *str2[] = {"cat",NULL};
	char *file[] = {NULL,NULL};
	char *file2[] = {"7","8","9",NULL};
		head->cmd=str;
		head->outfile = file;
		head->ofnum = 0;
		head->next->ofnum = 3;
		head->next->cmd=str2;
		head->next->outfile = file2;


	exe(head);
}
