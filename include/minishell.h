/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/26 17:57:51 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft/libft.h"
# include "../libft/printf/printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "./structs.h"
# include <stdio.h>
# include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
/*For global*/
t_ms	*ms(void);

/*For error*/

void	ex_error(char *message, t_error type, int err_status);
/*For shell*/
void	restart(int exit);
void	test();

/*For execute*/
/*<-----pipe && redirect----->*/
void	set_fd(t_cmd *cm);
pid_t	exe_pipe(t_cmd *cm);
pid_t	exe_pipe2(t_cmd *cm);
pid_t	exe_pipe3(t_cmd *cm);
pid_t 	pp_right_out(t_cmd *cm);
/*<-----exe----->*/
void	real_execute(t_cmd *cm);
# endif

