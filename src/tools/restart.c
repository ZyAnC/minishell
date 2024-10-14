/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/14 11:27:04 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"
void free_list(t_list *head)
{
	t_list *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}
void restart(int ex)
{//old code
	// if(!ms()->prompt)
	// 	free(ms()->prompt);
	// if(!ms()->input)
	// 	free(ms()->input);
	if (ms()->prompt)
		free(ms()->prompt);
	if(ms()->input)
		free(ms()->input);
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	free_token_list();
	free_cmd_list();
	if(ex)
	{
		free(ms()->cwd);
		pp_free(ms()->env);
		exit(ms()->exit);
	}
}

void	close_inout()
{
	if (ms()->in_fd != 0)
		close(ms()->in_fd);
	if (ms()->out_fd != 1)
		close(ms()->out_fd);
}

void	close_all(int	prev_fd)
{
	unlink("here_doc");
	if (prev_fd != -1)
		close(prev_fd);
	close_inout();
}
