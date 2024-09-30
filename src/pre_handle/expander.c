/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/30 09:37:42 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	The name doesn't not contain the '$' at the beginning.
	For example:
		1. $cat, will just return "cat" as the env_name;
*/
static char *get_env_name(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?');
		return (ft_strdup("$?"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (ft_substr(str, 0 , i));
}
/*
	This function will

*/
static void	add_to_env_list(char *env_name)
{
	char	*env_value;

	if (!env_name)
		return ;
	if (!ft_strcmp(env_name, "?"))
		env_value = ft_itoa(ms() ->exit);
	else
		env_value = get_env_value(env_name);
	
}

/*
	@How to check if the env is needed expaned or not?
	Rule: only when env is quoted by single quote, don't need expaned.
	The conditions need to be considerd:
		1. echo $?
		2. echo $$name
		3. echo "$name' abc"
		4. echo 'abc $name out"put'
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
		else if (str[i] == '$' && !is_seperator(str[i + 1]) && sg_quote)
		{
			add_to_env_list(get_env_name(&str[i + 1]));
			j = ft_strlen(get_env_name(&str[i + 1]));
		}
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
