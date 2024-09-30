/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:57:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/30 08:04:05 by jingwu           ###   ########.fr       */
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
	TK_WORD, // changed from TK_KEYWORD to TK_WORD
	TK_LOC_V,
}	t_token_type;

typedef enum e_err_type
{
	CMD,
	STX,
	F_NAME,
}	t_err_type;

/*
	To tell which node you want to pointer to in a link list;
	RESET: reset the pointer points the start of the list;
	NEXT: pointer moves to the next node in the list;
	CUR_COT: return the content of the current node;
	PRE_COT: return the content of the next node;
*/
typedef enum e_list_position
{
	RESET,
	NEXT,
	CUR_CNT,
	NEXT_CNT,
}	t_list_position;


typedef struct e_env
{
	char	*name;
	char	*value;
}	t_env;
/*
	@What is a token?
	It might be a command, a word or a redirector,and so on. Such as "echo", "hello", "<";

	@param
	str:	the content of a token, such as "echo", "abd" or "|";
	token:	the type of a token, such as "TK_PIPE" or "TK_APPEND"
*/
typedef struct s_token
{
	char			*str;
	t_token_type	tk_type;
}	t_token;

/*
	@param
	prompt:	the message showing in the shell
	input:	the commands that user input from terminal;
	tokens:	the token link list;
	cmds:	the command link list;
*/
typedef struct s_ms
{
	int				in_fd;
	int				out_fd;
	int				fd[2];
	int				exit;
	int				lines;
	char			**env;
	char			*cwd;
	char			*prompt;
	char			*input;
	char			*path;
	struct s_list	*tokens;
	struct s_list	*env_list;
	struct s_cmd	*cmds;
}	t_ms;

/*
	@param
	cmd:	the dyadic array of cmds. like "ls -l" will be stored as cmd[0]="ls", cmd[1]="-l"
	i_amt:	the amount of infiles;
	o_amt:	the amount of outfiles;
*/
typedef struct s_cmd
{
	char			**cmd;
	char			**infile;
	char			**outfile; // one single command might has more than 1 output files.
	t_token_type	intype;
	t_token_type	outype;
	int				i_amt;
	int				o_amt;
	int				prepipe; // default is 0;
	struct s_cmd	*next;
}	t_cmd;

# endif
