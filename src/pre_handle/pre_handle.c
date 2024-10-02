/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/02 11:11:14 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
	The function is add infiles, outfiles or delimiter for <, >, >> or << into their
	token arg.
*/
void	restruct_token(void)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*next;

	tmp = ms() ->tokens;

	while (tmp)
	{
		token = (t_token *)(tmp ->content);
		next = ((t_token *)((tmp ->next) ->content));
		if (is_dir(token))
		{
			token->arg = next->str;
			del_node(&(ms() ->tokens), tmp->next);
		}
		tmp = tmp->next;
	}
}

bool	pre_handle(void)
{
	if (!check_quote()) // it will check if the input is quoted correctly
		return (print_error(UNQUOTED, 1));
	if (!lexer())
		return (print_error(ADD_TOKEN_FAILED, 1));
	if (!check_syntax())
		return (false); // should return an error message here
	restruct_token();// add corresponding infos for redirections.
	expander();
	if (!parsing())
		return (false);

	if (check_all_local()) // what's this for?????
		return (false); // should return an error message here
	return (true);
}
