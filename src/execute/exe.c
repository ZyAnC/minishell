/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/02 08:33:05 by yzheng           ###   ########.fr       */
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


	if (cm->intype == TK_IN_RE)
		(ms()->in_fd) = open(cm->inf, O_RDONLY, 0444);
	if (cm->intype == TK_PIPE)
		(ms()->in_fd) = ms()->fd[0];
	//else if (cm->intype  == TK_HDOC)
	//	(ms()->in_fd) = heredoc(cm->infile);
	if (ms()->in_fd == -1)
	{
		if (!access(cm->inf, F_OK))
			ex_error(cm->inf, PREMISSON, 126);
		else
			ex_error(cm->inf,NFILE,2);
		restart(true);
	}
	else if (cm->outype  == TK_OUT_RE)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cm->outype == TK_APPEND)
		(ms()->out_fd) = open(cm->of, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cm->outype == TK_NONE)
		(ms()->out_fd) = STDOUT_FILENO;
	if (ms()->out_fd == -1)
	{
		if (!access(cm->inf, F_OK))
			ex_error(cm->inf, PREMISSON, 126);
		else
			ex_error(cm->inf,NFILE,2);
		restart(true);
	}
}
void	ex_error(char *message, t_error type, int err_status)
{
	ft_putstr_fd("minishell: ", 2);
	if(message)
		ft_putstr_fd(message, 2);
	if (type == DIRECTORY)
		ft_putstr_fd(": Is a directory", 2);
	else if (type == COMMAND)
		ft_putstr_fd(": command not found", 2);
	else if  (type == NFILE)
		ft_putstr_fd(": No such file or directory", 2);
	else if  (type == PREMISSON)
		ft_putstr_fd("Permission denied", 2);
	else if  (type == FORK)
		ft_putstr_fd("fork failed", 2);
	else if  (type == PIPE)
		ft_putstr_fd("pipe failed", 2);
	else if  (type == ERR)
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
	ft_printf("%s\n",cm->cmd[0]);
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
void	getdoc(char *av,int hfd)
{
	char	*doc_in;


	while (1)
	{
		doc_in = get_next_line(0);
		if (ft_strncmp(doc_in, av, ft_strlen(av)) == 0)
		{
			free(doc_in);
			break;
		}
		ft_putstr_fd(doc_in, hfd);
		free(doc_in);
	}
}
void exe(t_cmd *cm)
{
	pid_t pipeid;
	int prev_fd = -1;
	int i;

	i = 0;
	ms()->hfd = -1;
	while (cm)
	{
		set_fd(cm);
		if(cm->intype == TK_HDOC)
		{

			while(cm->herenum--)
			{

				ms()->hfd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (ms()->hfd == -1)
				{
					if (!access("here_doc", F_OK))
						ex_error("here_doc", PREMISSON, 126);
					else
						ex_error("here_doc",NFILE,2);
					restart(0);
				}
				getdoc(cm->limiter[i++],ms()->hfd);
				close(ms()->hfd);

			}
			cm->intype = TK_IN_RE;
			cm->inf = "here_doc";
			set_fd(cm);
		}

		if (cm->outype == TK_PIPE)
		{
			if (pipe(ms()->fd) == -1)
				ex_error("Pipe", PIPE, EXIT_FAILURE);
			pipeid = exe_pipe(cm);
			close(ms()->fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = ms()->fd[0];
		}
		else if((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
		&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE))
		{
			pipeid = exe_pipe2(cm);

		}

		else if (cm->intype == TK_PIPE &&
				(cm->outype == TK_OUT_RE || cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			pipeid = exe_pipe3(cm);
			close(ms()->fd[0]);
		}
		cm = cm->next;

	}
	if (prev_fd != -1)
		close(prev_fd);
	if (ms()->in_fd != 0)
		close(ms()->in_fd);
	if (ms()->out_fd != 1)
		close(ms()->out_fd);
	while (wait(NULL) > 0);


}


t_cmd *create_node( t_token_type intype, t_token_type outype) {
	t_cmd *new_node = malloc(sizeof(t_cmd));
	if (!new_node) {
		perror("Failed to allocate memory");
		return NULL;
	}

	new_node->cmd = NULL;


	new_node->intype = intype;
	new_node->outype = outype;
	new_node->prepipe = 0;
	new_node->next = NULL;

	return new_node;
}
void	test()
{
	t_cmd *head = create_node(TK_HDOC, TK_NONE);

	t_cmd *second = create_node(TK_PIPE,TK_NONE);


t_cmd *third = create_node(TK_NONE,TK_NONE);
		//head->next = third;
		//second->next = third;
	char *str[] = {"cat",NULL};
	char *str2[] = {"cat",NULL};
	char *str3[] = {NULL};
	char *file[] = {NULL};
	char *file2[] = {NULL,NULL};
	char *file3[] = {NULL,NULL};

		head->cmd=str;
		head->outfile = file;
		head->of = NULL;
		head->ofnum = 0;
		head->inf = "here_doc";
		head->ifnum = 0;

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
	head->herenum = 3;
		head->infile = infile;
			third->infile = infile3;

	exe(head);

}
