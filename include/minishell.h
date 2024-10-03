/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/03 11:07:45 by jingwu           ###   ########.fr       */
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
# define MEMORY_ERROR		"Unable to allocate memory."
# define UNQUOTED			"The input is quoted incorrectly."
# define ADD_TOKEN_FAILED	"Failed when trying to add a new node to token list."
# define PIPE_STX_ERR		"minishell: syntax error near unexpected token `|'"
# define NL_STX_ERR			"minishell: syntax error near unexpected token `newline'"
# define IN_RE_STX_ERR		"minishell: syntax error near unexpected token `<'"
# define OUT_RE_STX_ERR		"minishell: syntax error near unexpected token `>'"
# define HDOC_STX_ERR		"minishell: syntax error near unexpected token `<<'"
# define APED_STX_ERR		"minishell: syntax error near unexpected token `>>'"
# define ADD_CMD_ERR		"Failed to add a new command node"


/*For global*/
t_ms	*ms(void);

/*For shell*/
void	restart(int exit);

/*                                             pre_handle                                               */

// add_cmd_utils.c
void	count(t_cmd **cmd, t_list *tk_lt, int start, int end);
bool	allocate_mem(t_cmd **cmd);

// checking.c
bool	check_syntax(void);
bool	check_quote(void);
bool	check_mergerable(char *matcher, char *str, int index);

// expander.c
void	expander(void);

// lexer.c
bool	lexer(void);

// operate_token.c
t_token	*new_token(char *str, t_token_type tk_type, bool merge);
int	add_token(char *str, t_token_type token, bool merge);
t_token	*tk_list_manager(t_list_position psn);
void	del_node(t_list **list, t_list *node);

// parsing.c
bool	parsing(void);

// pre_handle.c
void	restruct_token(void);
bool	pre_handle(void);

// process_re.c
void	process_re(t_cmd **cmd, t_list *tk_node);

/*                                              tools                                                    */
// handle_error.c
bool	print_error(char *err_type, int err_fd);
bool	stx_error(t_token *node);

// utils.c
bool	is_pipe(t_token *token);
bool	is_dir(t_token *token);
bool	is_dir_or_pipe(t_token *token);
bool	is_seperator(char c);

// env_list.c
char	*get_env_value(char *env_name);

# endif
