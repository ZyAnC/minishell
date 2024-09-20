/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:57:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/20 11:22:16 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_tokens
{
	PIPE,
	IN_RDRCT,
	OUT_RDRCT,
	HERE_DOC,
	APPEND_RDRCT,
}	e_tokens;

typedef struct s_lexer
{
	char			*str;
	e_tokens		token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

typedef struct s_parser
{
	t_lexer			*s_lexer_list;
	t_lexer			*redirections;
	int				num_rdrct;
	struct s_tools	*tools;
}	t_parser;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools, struct s_cmds *);
	int						*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*pre;
}	t_cmds;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						num_pipe;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_tools;

# endif
