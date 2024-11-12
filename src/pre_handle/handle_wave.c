/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:54:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/11/12 11:50:09 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_wave(char *str)
{
	char	*value;
	char	*newstr;
	char	*tmp;
	char	*s;

	value = get_variable_value("HOME");
	tmp = ft_strjoin(value, "/");
	s = str;
	s++;
	s++;
	newstr = ft_strjoin(tmp, s);
	ft_free_str(str);
	ft_free_str(value);
	ft_free_str(tmp);
	if (!newstr)
		return (NULL);
	return (newstr);
}

/*
	@function
	To check if there is '~' sign, and if it is needs to be replaced by
	home path.

	@When the '~' is needed be replaced? It must be fullfilled the below
	conditions:
	1.the string is not inside any quotation mark.
	2.'~' is the first letter of the string;
	3.the letter following '~' is '/';
*/
bool	handle_wave_sign(t_list *list)
{
	t_token	*token;

	while(list)
	{
		token = (t_token *)list->content;
		if (token->tk_type != TK_DOUBLE_QT && token->tk_type != TK_SINGLE_QT
			&& token->str && !ft_strncmp(token->str, "~/", 2))
		{
			token->str = replace_wave(token->str);
			if(!token->str)
				return (print_error("Replace wave sign error!" ,2));
		}
		list = list->next;
	}
	return (true);
}
