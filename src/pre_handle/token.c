/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:32:38 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/23 13:39:50 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


int	add_token(char *tk_str, t_token_type type, bool mergeable)
{
	t_token	*token;

	if (!tk_str || !*tk_str)
		return (0);
	token = new_token(tk_str, type, mergeable);
	if (!token)

}
