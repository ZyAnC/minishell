/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:50 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/01 18:05:08 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void restart(int ex)
{

    if(!ms()->prompt)
      free(ms()->prompt);
    if(!ms()->input)
        free(ms()->input);
    ms()->fd[0] = -1;
	ms()->fd[1] = -1;
    ms()->in_fd = STDIN_FILENO;
    ms()->out_fd = STDOUT_FILENO;

    if(ex)
    {
        free(ms()->cwd);
        exit(ms()->exit);
    }
}
