/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:14:19 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/04 11:41:43 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@What the function does?
	To listening SIGINT (ctrl-C) and SIGQUIT(ctrl-\)
*/
void	init_signal(void)
{
//	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
