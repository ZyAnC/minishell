/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:24:00 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/14 13:38:49 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_newfree(void *pointer)
{
	if (pointer)
		free(pointer);
	pointer = NULL;
}

void	pp_free(char **fly)
{
	int	j;

	if (!fly || !*fly)
		return ;
	j = 0;
	while (fly[j])
			free(fly[j++]);
	free(fly);
	fly = NULL;
}

void	free_token_list(void)
{
	t_list	*temp;
	t_list	*next_node;
	t_token	*token;

	if (ms()->tokens == NULL)
		return ;
	temp = ms()->tokens;
	while (temp)
	{
		token = temp->content;
		next_node = temp->next;
		ft_newfree(token->arg);
		ft_newfree(token->str);
		free(temp);
		temp = next_node;
	}
	ms()->tokens = NULL;
}

void free_cmd_list(void)
{
	t_cmd	*next_cmd;

	if (!ms()->cmds)
		return ;
	while (ms()->cmds)
	{
		next_cmd = ms()->cmds->next;
		pp_free(ms()->cmds->cmd);
		pp_free(ms()->cmds->infile);
		pp_free(ms()->cmds->limiter);
		pp_free(ms()->cmds->outfile);
		ft_newfree(ms()->cmds->of);
		ft_newfree(ms()->cmds->inf);
		free(ms()->cmds);
		ms()->cmds = next_cmd;
	}
	ms()->cmds = NULL;
}
