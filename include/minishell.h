/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/26 14:20:49 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	<stdio.h>:	printf();
	<stdbool.h>	bool type;
	<readline/readline.h>	readline();
	<readline/readline.h>	operate the readline history;
	<fcntl.h>	the flags when open a file;
	<signal.h>	the signal functions;
	<unistd.h>	for STDERR_FILENO
*/
# include "../libft/libft/libft.h"
# include "../libft/printf/printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "./structs.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/*                                             err_type                                         */
# define MEMORY_ERROR	"Unable to allocate memory."
# define UNQUOTED		"The input is quoted incorrectly."
# define ADD_TOKEN_FAILED	"Failed when trying to add a new node to token list."
# define PIPE_STX_ERR	"bash: syntax error near unexpected token `|'"


/*For global*/
t_ms	*ms(void);

/*For shell*/
void	restart(int exit);

/*                                             pre_handle                                               */
// pre_handle.c
bool	pre_handle(void);

// lexer.c
bool	lexer(void);

// operate_lexer.c
t_token	*new_token(char *str, t_token_type tk_type);
bool	add_token(char *str, t_token_type token);
t_token	*tk_list_manager(t_list_position psn);

// checking.c
bool	check_syntax(void);
bool	check_quote(void);

/*                                              tools                                                    */
// handle_error.c
bool	print_error(char *err_type, int err_fd);

// utils.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);

# endif
