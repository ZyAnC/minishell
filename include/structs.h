/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:57:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/25 13:55:04 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include "minishell.h"

typedef enum e_token_type
{
	TK_NONE,
	TK_PIPE,
	TK_IN_RE,
	TK_OUT_RE,
	TK_HDOC,
	TK_APPEND,
	TK_SINGLE_QT,
	TK_DOUBLE_QT,
	TK_KEYWORD,
	TK_LOC_V,
}	t_token_type;

typedef enum e_err_type
{
	COMMAND,
	SYNTAX,
}	t_err_type;

/*
	tk_str: the chararters of the token, such as "|", "<<", ans so on;
	type:  the type of the token, such as "TK_PIPE", "TK_APPEND";
*/
// typedef struct s_token
// {
// 	char			*tk_str;
// 	t_token_type	type;
// }	t_token;

typedef struct s_lexer
{
	char			*str;
	t_token_type	token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

/*
	prompt: the message showing in the shell
	input: the commands that user input from terminal;
*/
typedef struct s_ms
{
	int				in_fd;
	int				out_fd;
	int				fd[2];
	int				exit;
	int				lines;
	char				**env;
	char				*cwd;
	char				*prompt;
	char				*input;
	char				*path;
	struct s_lexer	*lexer_list;
	struct s_cmd		*cmds;
}	t_ms;

typedef struct s_cmd
{
	char			**cmd;
	char			*infile;
	char			**outfile; // one single command might has more than 1 output files.
	t_token_type	intype;
	t_token_type	outype;
	int				ispipe;
	int				prepipe; // default is 0;
	struct s_cmd	*next;
}	t_cmd;

# endif
