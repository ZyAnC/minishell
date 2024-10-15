/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:43:11 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/15 12:01:08 by jingwu           ###   ########.fr       */
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
	int		i;
//	char	*substr;
//	char	*start;
//printf("passed str=%s\n", str);//for testing!!!!!
	// substr = ft_strchr(str, '$');
	// start = substr;
	// substr++;
	// if (*substr == '?')
	// 	return (ft_strdup("$?"));
	// while (*substr && (ft_isalnum(*substr) || *substr == '_'))
	// 	substr++;
	// printf("name=%s\n",ft_substr(str, (start - str) , (substr - str)));//for testing!!!!!!!!!!!!!!!!!!!!!!
	// return (ft_substr(str, (start - str) , (substr - str)));
	i = 0;
	if(str[i] == '$')
		i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
//	printf("the name is=%s\n", ft_substr(str, 0 , i));//for testing!!!!!
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
	tmp = ft_strnstr(str, name, (ft_strlen(str)));
	bef_name = ft_substr(str, 0, (tmp - str));
	ft_strlcat(newstr, bef_name, (len + 1));
	ft_strlcat(newstr, value, (len + 1));
	ft_strlcat(newstr, (tmp + ft_strlen(name)), len + 1);
	free(bef_name);
//	printf("newstr=%s\n", newstr);//for testing!!!!!!!!!!!!!!!!!!!!!!
	return (newstr);
}

static void	expand(t_token *token)
{//int i = 0;// for testing!!!!!!!!!!
	char	*name;
	char	*value;
	char	*tmp;

	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
//		printf("<-------------------inside while loop----------%d-------->\n", i++);//for testing!!!!!!!!!!!!!!!!!!!
		name = get_env_name(ft_strchr(token->str, '$'));
//		printf("name=%s\n", name);//for testing!!!!!!!!!!!!!!!!!!!!
		if (!name)
			return ;
		if (!ft_strcmp(name, "$?"))
			value = ft_itoa(ms() ->exit);
		else
			value = get_variable_value(name);
//		printf("value=%s\n", value);//for testing!!!!!!!!!!!!!!!!!!!!
		tmp = token->str;
		token->str = replace(token->str, name, value);
//		printf("token->str=%s\n", token->str);//for testing!!!!!!!!!!!!!!!!!!!!
		free(name);
		free(value);
		free(tmp);
	}
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
//printf("<-------------------inside expander------------------>\n");//for testing!!!!!!!!!!!!!!!
	tk_list_manager(RESET);
//printf("<-------------------1----------------->\n");//for testing!!
	while (tk_list_manager(CUR_CNT))
	{//printf("<-------------------2----------------->\n");//for testing!!
		token = tk_list_manager(CUR_CNT);
//		printf("<-------------------3----------------->\n");//for testing!!
		if (token->tk_type == TK_DOUBLE_QT || token->tk_type == TK_WORD)
		{
			str = ft_strchr(token->str, '$');
//			printf("<-------------------4----------------->\n");//for testing!!
			if (str && *(str + 1) != '\0' && *(str + 1) != ' ' )
			{
//				printf("<-------------------going to expand()------------------>\n");//for testing!!!!!!!!!!!!!!!!!!!!
				expand(token);
			}
		}
		if (ft_strchr(token->str, '=') && is_defining_var(token->str))
			token->tk_type = TK_LOC_V;
		tk_list_manager(NEXT);
	}
}
