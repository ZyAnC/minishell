/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/09 14:47:44 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The name doesn't not contain the '$' at the beginning.
	For example:
		1. $cat, will just return "$cat" as the env_name;
*/
static char *get_env_name(char *str)
{
	int	i;
printf("inside get_env_name\n");// for test!!!!!!!!!!!!!!!!!!
	i = 0;
	if(str[i] == '$')
		i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;

	return (ft_substr(str, 0 , i));
	printf("out of get_env_name\n");// for test!!!!!!!!!!!!!!!!!!
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
printf("inside replace\n");// for test!!!!!!!!!!!!!!!!!!
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
	printf("out of replace\n");// for test!!!!!!!!!!!!!!!!!!
}

static void	expand(t_token *token)
{
	char	*name;
	char	*value;
	char	*tmp;
printf("inside expand\n");// for test!!!!!!!!!!!!!!!!!!
	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
		name = get_env_name(token->str);
		if (!name)
			return ;

		if (!ft_strcmp(name, "$?"))
			value = ft_itoa(ms() ->exit);
		else
			value = get_env_value(name);
		printf("Here2\n");
		tmp = token->str;
		token->str = replace(token->str, name, value);
		printf("Here3\n");
		free(name);
		free(value);
		free(tmp);

		printf("Here4\n");
	}
	printf("out of expand\n");// for test!!!!!!!!!!!!!!!!!!
}
/*
	@How to check if the env is needed expaned or not?
	Rule: when env is quoted by double quote, or not quoted, they need to expand.
	The conditions need to be considerd:
		1. echo $?
		2. echo $$name
		3. echo "$name' abc"
		4. echo 'abc $name out"put'
*/
void	expander(void)
{
	t_token	*token;
	char	*str;

	tk_list_manager(RESET);
	while (tk_list_manager(CUR_CNT))
	{
		token = tk_list_manager(CUR_CNT);
		if (token->tk_type == TK_DOUBLE_QT || token->tk_type == TK_WORD)
		{
			str = ft_strchr(token->str, '$');
			if (str && *(str + 1) != '\0' && *(str + 1) != ' ' )
				expand(token);
		}
		if (ft_strchr(token->str, '=') && is_defining_var(token->str))
			token->tk_type = TK_LOC_V;
		tk_list_manager(NEXT);
	}
}
