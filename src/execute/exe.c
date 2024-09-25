/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/25 12:17:14 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./minishell.h"

void	set_fd(t_cmd *cm)
{
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
void	ex_error()
{
	exit(1);
}


/*
	is_pipe means cmd before pipe ls -l |					exe_pipe
	is_pipe && prepipe mean cmd between 2 pipe | ls -l |	exe_pipe2
	prepipe means cmd behind pipe | ls -l					exe_pipe3

*/
void	real_execute(t_cmd *cm)
{
	int i = 0;
	while(cm->cmd[i])
		ft_printf("%s\n",cm->cmd[i++]);
	i = 1;
	ft_printf("%s\n",ms()->path);
	ft_printf("%s\n",ms()->input);

}
void	exe(t_cmd *cm)
{
	while (cm)
	{
		set_fd(cm);
		if (cm->outype == TK_PIPE && cm->prepipe == 0)
			exe_pipe(cm);
		else if (cm->outype == TK_PIPE && cm->prepipe == 1)
			exe_pipe2(cm);
		else if (cm->outype != TK_PIPE && cm->prepipe == 1)
			exe_pipe3(cm);
		else if (cm->outype != TK_PIPE && cm->prepipe == 0)
			exe_simple(cm);
		cm = cm->next;
	}
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
	t_cmd *head = create_node(NULL, NULL, TK_NONE, TK_NONE, 0);

	t_cmd *second = create_node(NULL, NULL, TK_NONE, TK_NONE, 0);


	if (head && second) {
		head->next = second;
	char *str[] = {"cat", NULL};
	char *str2[] = {"grep","txt", NULL};
		head->cmd=str;


		head->next->cmd=str2;
	}
	ft_printf("%d\n",ms()->in_fd);
	ft_printf("%d\n",ms()->out_fd);
	exe(head);
	//ft_printf("qqqqqq\n");
}
