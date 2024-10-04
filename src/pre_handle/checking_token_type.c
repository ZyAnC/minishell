/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_token_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:47:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/04 11:37:50 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool	is_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_PIPE)
		return (true);
	return (false);
}

bool	is_dir(t_token *token)
{
	if (!token)
		return (false);
	if (token->tk_type == TK_IN_RE || token->tk_type == TK_OUT_RE
		|| token->tk_type == TK_HDOC || token->tk_type == TK_APPEND)
		return (true);
	return (false);
}

bool	is_dir_or_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (is_pipe(token) || is_dir(token))
		return (true);
	return (false);
}
/*
	Here the seperators contain:|, <,>,',", space, \0,
*/
bool	is_seperator(char c)
{
	char	*sep;

	sep = "|<>\'\"\0 ";
	if (!ft_strchr(sep, c))
		return (false);
	return (true);
}

/*
	The syntax of defining  enviroment varible: name=value
	Rule:
	1. there is no space between "name", "=" and "value", like
	   name =123, name= 123 are all wrong;
	2. the variable name only start with either letter or '_', and only
	   contains letter, '_' and number.
	   like 2name=123, *name=123, na$me=123 are all wrong;

	f_equal: when loop the str, if encounter a "=" then f_equal=true;
	f_alp_uds: when loop the str, if encounter a alphabeta or "_", then
				f_alp_uds=true;
*/
bool	is_defining_var(t_token *token)
{
	int		i;
	bool	f_equal;
	bool	f_alp_uds;

	i = -1;
	f_equal = false;
	f_alp_uds = false;
	while (token->str[++i])
	{
		if (token->str[i] == '=')
			f_equal = true;
		else if (token->str[i] == '_' || ft_isalpha(token->str[i]))
			f_alp_uds = true;
		else if (!ft_isalpha(token->str[i]) && token->str[i] != '_'
			&& !f_equal && !f_alp_uds)
			return (false);
		else if (!ft_isalnum(token->str[i]) && token->str[i] != '_'
			&& !f_equal)
			return (false);
	}
	add_env_node(&(ms() ->env_list), token->str);
	return (true);
}
