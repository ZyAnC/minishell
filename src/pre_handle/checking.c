/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:55:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/26 14:41:03 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	@param
	flag:
		false: unclosed quote;
		true: closed quote;
*/
bool	check_quote(void)
{
	int		i;
	char	quote;
	bool	flag;

	i = 0;
	flag = true;
	while (ms()->input[i])
	{
		if (flag && ft_strchr("\"\'", ms()->input[i]))
		{
			quote = ms()->input[i];
			flag = false;
		}
		else if (!flag && ms()->input[i] == quote)
			flag = true;
		i++;
	}
	if (!flag)
	{
		print_error(UNQUOTED, 1);
		return(false);
	}
	return (true);
}

/*
	@What condistions count as an error?
	1. the command starts with '|';
	2. (somthing command) meta_char meta_char1;
	3.
*/
bool	check_syntax(void)
{
	t_token	*next;

	tk_list_manager(RESET);
	if (!is_pipe(tk_list_manager(CUR_COT)))
		return(print_error(PIPE_STX_ERR, 1));
	while (tk_list_manager(CUR_COT))
	{
		next = tk_list_manager(NEXT_COT);
		if (is_dir(tk_list_manager(CUR_COT)
			&& (!next || is_dir_or_pipe(tk_list_manager(NEXT_COT)))))
			return(print_error(?????, 1));/// define the error type
	}
}
