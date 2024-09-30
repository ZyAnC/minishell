/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/30 10:48:38 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	The name doesn't not contain the '$' at the beginning.
	For example:
		1. $cat, will just return "$cat" as the env_name;
*/
static char *get_env_name(char *str)
{
	int	i;

	i = 0;
	if(str[i] == '$')
		i++;
	if (str[i] == '?');
		return (ft_strdup("$?"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (ft_substr(str, 0 , i));
}
/*
	The function will replace name with value, then return the newstr.
*/
static char	*replace(char *str, char *name, char *value)
{
	int		len;
	char	*newstr;
	char	*tmp;
	char	*bef_name;

	if (!str | !name | !value)
		return (ft_strdup(""));
	len = ft_strlen(str) + ft_strlen(value) - ft_strlen(name);
	newstr = ft_calloc((len + 1), sizeof(char));
	if (!newstr)
		return (ft_strdup(""));
	tmp = ft_strnstr(str, name, (ft_strlen(str))); // find the start position of the name
	bef_name = ft_substr(str, 0, (tmp - str));
	ft_strlcat(newstr, bef_name, (len + 1));
	ft_strlcat(newstr, value, (len + 1));
	ft_strlcat(newstr, (tmp + ft_strlen(name)), len + 1);
	free(bef_name);
	return (newstr);
}

/*
	This function will ge the env_value first, then call function
	replace() to replace the env_name with env_value.

*/
static void	replace_env(t_token *token, char *env_name)
{
	char	*env_value;
	int		len;
	char	*new_str;

	if (!token || !env_name)
		return ;
	if (!ft_strcmp(env_name, "$?"))
		env_value = ft_itoa(ms() ->exit);
	else
		env_value = get_env_value(env_name);
	token->str = replace(token->str, env_name, env_value);
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
static void	expand(t_token *token)
{
	bool	sg_quote;
	bool	db_quote;
	int		i;
	int		j;

	sg_quote = false;
	db_quote = false;
	i = 0;
	while (token->str[i])
	{
		j = 1;
		if (token->str[i] == '\"' && !sg_quote && !db_quote)
			db_quote = true;
		else if (token->str[i] == '\'' && !db_quote && !sg_quote)
			sg_quote = true;
		else if (token->str[i] == '$' && !is_seperator(token->str[i + 1])
			&& sg_quote)
		{
			replace_env(token, get_env_name(&(token->str[i])));
			j = ft_strlen(get_env_name(&(token->str[i])));
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
				expand(token);// inside expand()it may do not expand.
		}
		tk_list_manager(NEXT);
	}
}
