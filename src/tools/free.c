/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:24:00 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/11 14:26:39 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_newfree(void *pointer)
{
	if (pointer)
		free(pointer);
	pointer = NULL;
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
	print_list(ms()->tokens, 1);// for test
}

// void free_cmd_list(t_cmd *command)
// {
// 	t_cmd *next_cmd;  // 临时变量，用来保存下一个节点

// 	while (command)
// 	{
// 		next_cmd = command->next;  // 保存下一个节点指针

// 		// Free the cmd array
// 		if (command->cmd)
// 		{
// 			for (int i = 0; command->cmd[i] != NULL; i++)
// 			{
// 				free(command->cmd[i]); // Free each string in the cmd array
// 			}
// 			free(command->cmd); // Free the cmd array itself
// 		}

// 		// Free the infile array
// 		if (command->infile)
// 		{
// 			for (int i = 0; command->infile[i] != NULL; i++)
// 			{
// 				free(command->infile[i]); // Free each string in the infile array
// 			}
// 			free(command->infile); // Free the infile array itself
// 		}

// 		// Free the limiter array
// 		if (command->limiter)
// 		{
// 			for (int i = 0; command->limiter[i] != NULL; i++)
// 			{
// 				free(command->limiter[i]); // Free each string in the limiter array
// 			}
// 			free(command->limiter); // Free the limiter array itself
// 		}

// 		// Free the outfile array
// 		if (command->outfile)
// 		{
// 			for (int i = 0; command->outfile[i] != NULL; i++)
// 			{
// 				free(command->outfile[i]); // Free each string in the outfile array
// 			}
// 			free(command->outfile); // Free the outfile array itself
// 		}

// 		// Free the strings if they are allocated
// 		free(command->of);
// 		free(command->inf);
// 		command->word = 0;
// 		// Free the command structure itself
// 		free(command);

// 		// Move to the next command in the list
// 		command = next_cmd;
// 	}
//  ms()->cmds = NULL; 
// 	//print_cmd(); // For testing
// 	printf("<----------------------->\n");
// }


// /*
// 	1: print tokens
// 	2: print env;
// */
// void	print_list(t_list *list, int flag)// for test !!!!!!!!!!!!!!!!!!!!!!!!
// {
// 	t_token	*token;
// 	t_env	*env;
// 	int		i;

// 	i = 0;
// 	if (!list)
// 	{
// 		printf ("token list is empty\n");
// 		return ;
// 	}

// 	while (list)
// 	{
// 		if (flag == 1)
// 		{
// 			token = list->content;
// 			printf("token[%d]: str=%s   type=%u  arg=%s  index=%d  merger=%d\n", i, token->str, token->tk_type, token->arg, token->idx, token->merge);
// 		}
// 		else if (flag == 2)
// 		{
// 			env = list->content;
// 			printf("env[%d]: name=$%s   value=%s\n", i, env->name, env->value);
// 		}
// 		i++;
// 		list = list->next;
// 	}
// }

// void	print_cmd(void)// for test !!!!!!!!!!!!!!!!!!!!!!!!
// {
// 	t_cmd	*cmd;
// 	int  i_cmd = 0;
// 	int	j;

// 	if (!ms()->cmds)
// 	{
// 		printf ("cmd list is empty\n");
// 		return ;
// 	}

// 	cmd = ms()->cmds;
// 	while (cmd)
// 	{
// 		j = 0;
// 		printf("cmd[%d]\n", i_cmd++);
// 		printf("ofnum=%d  ifnum=%d  herenum=%d  word=%d\n", cmd->ofnum, cmd->ifnum, cmd->herenum, cmd->word);
// 		if (cmd->word != 0)
// 		{
// 			printf("\ncmd strs are below:\n");
// 			while(j < cmd->word)
// 			{
// 				printf("	cmd_str[%d]=%s\n", j, cmd->cmd[j]);
// 				j++;
// 			}
// 		}
// 		j = 0;
// 		if (cmd->ifnum != 0)
// 		{
// 			printf("\ninfile strs are below:\n");
// 			while(j < cmd->ifnum)
// 			{
// 				printf("	infile[%d]=%s\n", j, cmd->infile[j]);
// 				j++;
// 			}
// 		}
// 		j = 0;
// 		if (cmd->ofnum != 0)
// 		{
// 			printf("\noutfile strs are below:\n");
// 			while(j < cmd->ofnum)
// 			{
// 				printf("	outfile[%d]=%s\n", j, cmd->outfile[j]);
// 				j++;
// 			}
// 		}
// 		j = 0;
// 		if (cmd->herenum)
// 		{
// 			printf("\nlimiter strs are below:\n");
// 			while(j < cmd->herenum)
// 			{
// 				printf("	limiter[%d]=%s\n", j, cmd->limiter[j]);
// 				j++;
// 			}
// 		}
// 		printf("\nlast_infile=%s\nlast_outfie=%s", cmd->inf, cmd->of);
// 		printf("\nintype=%d\nouttype=%d\n\n", cmd->intype, cmd->outype);
// 		cmd = cmd->next;
// 	}
// }
