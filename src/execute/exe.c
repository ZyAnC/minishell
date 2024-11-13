/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:53:13 by yzheng            #+#    #+#             */
/*   Updated: 2024/11/13 09:29:21 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	check_signal(int b)
{
	if (ms()->exit == 130 && b > 1)
		printf("\n");
	if (ms()->exit == 130 && b == 1)
		restart(0);
}

static int	exe_heart(int i, t_cmd *cm, int *prev_fd, int b)
{
	if (i)
	{
		if (cm->herenum > 0)
			type_hdoc(cm);
		if (!cm->cmd)
			return (1);
		if (ms()->exit == 130 && ms()->hstatus == 1)
			return (1);
		if (cm->outype == TK_PIPE)
			type_outpipe(cm, prev_fd);
		else if ((cm->intype == TK_IN_RE || cm->intype == TK_NONE)
			&& (cm->outype == TK_OUT_RE || cm->outype == TK_NONE
				|| cm->outype == TK_APPEND))
			exe_pipe2(cm);
		else if (cm->intype == TK_PIPE && (cm->outype == TK_OUT_RE
				|| cm->outype == TK_NONE || cm->outype == TK_APPEND))
		{
			exe_pipe3(cm);
			close(ms()->fd[0]);
		}
		check_signal(b);
	}
	return (1);
}

int	check_cat(t_cmd *cm, int i, int b, int prev_fd)
{
	i = set_fd(cm);
	if (!i && (!ft_strncmp(cm->cmd[0], "cat", 3)
			|| !ft_strncmp(cm->cmd[0], "grep", 4)))
	{
		cm = cm->next;
		if (cm && !ft_strncmp(cm->cmd[0], "cat", 3)
			&& cm->intype == TK_PIPE)
		{
			ms()->exit = 0;
			return (0);
		}
		return (1);
	}
	if (!cm->cmd && cm->intype != TK_HDOC)
		return (0);
	if (b == 1 && cm->outype == TK_NONE && cm->intype != TK_HDOC)
		if (ft_strncmp(cm->cmd[0], "echo", 4)
			&& ft_strncmp(cm->cmd[0], "pwd", 3) && builtin(cm->cmd))
			return (0);
	exe_heart(i, cm, &prev_fd, b);
	return (2);
}

void	exe(t_cmd *cm)
{
	int		prev_fd;
	int		i;
	int		b;
	int		status;

	i = 0;
	prev_fd = -1;
	b = count_cm(cm);
	while (cm)
	{
		status = check_cat(cm, i, b, prev_fd);
		if (status == 0)
			break ;
		else if (status == 1)
			continue ;
		if ((ms()->exit == 130 && ms()->hstatus == 1))
			break ;
		cm = cm->next;
	}
	close_all(prev_fd);
	exe_final();
}
