#include "minishell.h"

// void free_cmd_list(void)
// {
// printf("<------------get in free cmd list----------->\n");// For testing!!!!!!!!!!!!!!!!!!!!!!!!!
// 	t_cmd	*next_cmd;

// 	if (!ms()->cmds)
// 	{
// 		printf("inside free_cmd_list, ms()->cmd is empty\n");
// 		return ;
// 	}
// 	while (ms()->cmds)
// 	{
// 		next_cmd = ms()->cmds->next;
// 		printf("<--------------------1---------------------->\n");
// 		pp_free(ms()->cmds->cmd);

// 		printf("<--------------------2---------------------->\n");
// 		pp_free(ms()->cmds->infile);

// 		printf("<--------------------3---------------------->\n");
// 		pp_free(ms()->cmds->limiter);

// 		printf("<--------------------4---------------------->\n");
// 		pp_free(ms()->cmds->outfile);

// 		printf("<--------------------5---------------------->\n");
// 		if (ms()->cmds->of)
// 			free(ms()->cmds->of);

// 		printf("<--------------------6---------------------->\n");
// 		if (ms()->cmds->inf)
// 			free(ms()->cmds->inf);

// 		printf("<--------------------7---------------------->\n");
// 		free(ms()->cmds);

// 		printf("<--------------------8---------------------->\n");
// 		ms()->cmds = next_cmd;
// 		printf("<--------------------9---------------------->\n");
// 	}
// 	printf("<--------------------10---------------------->\n");
// 	ms()->cmds = NULL;
// 	printf("finishing free cmd list\n");// For testing!!!!!!!!!!!!!!!!!!!!!!!!!
// 	print_cmd(); // For testing!!!!!!!!!!!!!!!!!!!!!!!!!
// }


/*
	1: print tokens
	2: print env;
	3: print local variable
*/
void	print_list(t_list *list, int flag)// for test !!!!!!!!!!!!!!!!!!!!!!!!
{
	t_token	*token;
	t_env	*env;
	int		i;

	i = 0;
	if (!list)
	{
		printf ("token list is empty\n\n");
		return ;
	}

	while (list)
	{
		if (flag == 1)
		{
			token = list->content;
			printf("token[%d]: str=%s   type=%u  arg=%s  index=%d  merger=%d\n", i, token->str, token->tk_type, token->arg, token->idx, token->merge);
		}
		else if (flag == 2)
		{
			env = list->content;
			printf("env[%d]: name=$%s   value=%s\n", i, env->name, env->value);
		}
		else if (flag == 3)
		{
			env = list->content;
			printf("local_var[%d]: name=$%s   value=%s\n", i, env->name, env->value);
		}
		i++;
		list = list->next;
	}
	printf ("\n\n");
}

void	print_cmd(void)// for test !!!!!!!!!!!!!!!!!!!!!!!!
{//printf("get into print_cmd function\n");// for test !!!!!!!!!!!!!!!!!!!!!!!
	t_cmd	*cmd;
	int  i_cmd = 0;
	int	j;

	if (!ms()->cmds)
	{
		printf ("cmd list is empty\n\n");
		return ;
	}

	cmd = ms()->cmds;
	while (cmd)
	{
		j = 0;
		printf("cmd[%d]\n", i_cmd++);
		printf("ofnum=%d  ifnum=%d  herenum=%d  word=%d\n", cmd->ofnum, cmd->ifnum, cmd->herenum, cmd->word);
		if (cmd->word != 0)
		{
			printf("\ncmd strs are below:\n");
			while(j < cmd->word)
			{
				printf("	cmd_str[%d]=%s\n", j, cmd->cmd[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->ifnum != 0)
		{
			printf("\ninfile strs are below:\n");
			while(j < cmd->ifnum)
			{
				printf("	infile[%d]=%s\n", j, cmd->infile[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->ofnum != 0)
		{
			printf("\noutfile strs are below:\n");
			while(j < cmd->ofnum)
			{
				printf("	outfile[%d]=%s\n", j, cmd->outfile[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->herenum)
		{
			printf("\nlimiter strs are below:\n");
			while(j < cmd->herenum)
			{
				printf("	limiter[%d]=%s\n", j, cmd->limiter[j]);
				j++;
			}
		}
		printf("\nlast_infile=%s\nlast_outfie=%s", cmd->inf, cmd->of);
		printf("\nintype=%d\nouttype=%d\n\n", cmd->intype, cmd->outype);
		cmd = cmd->next;
	}
	printf ("\n\n");
}
