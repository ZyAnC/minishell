/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:55:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/23 10:36:46 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
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
		ft_err("Unclosed quote!", STX, 1);
		return(false);
	}
	return (true);
}
