/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/27 13:01:40 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char *get_env_name()
{
	
}
/*
	This function will 
	@return
		the length of the env_name: when replace successfully;
		1: when it doesn't replace.
*/
static int	replace_env(char *env_name)
{
	
}

/*
	@How to check if the env is needed expaned or not?
	Rule: only when env is quoted by single quote, don't need expaned.
	
*/
static void	expand(char *str)
{
	bool	sg_quote;
	bool	db_quote;
	int		i;
	int		j;

	sg_quote = false;
	db_quote = false;
	i = 0;
	while (str[i])
	{
		j = 1;
		if (str[i] == '\"' && !sg_quote && !db_quote)
			db_quote = true;
		else if (str[i] == '\'' && !db_quote && !sg_quote)
			sg_quote = true;
		else if (str[i] == '$' && str[i + 1] != '$' && sg_quote)
			j = replace_env(get_env_name());
		i += j;
	}
}

void	expander(void)
{
	t_token	*token;
	int		i;

	tk_list_manager(RESET);
	while (tk_list_manager(CUR_CNT))
	{
		token = tk_list_manager(CUR_CNT);
		if (token->tk_type == TK_WORD)
		{
			if (ft_strchr(token->str, '$'))
				expand(token->str);// inside expand()it may do not expand.
		}
		tk_list_manager(NEXT);
	}
}
