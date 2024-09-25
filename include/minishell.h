/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/25 10:38:59 by jingwu           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/*                                             Errors_define                                            */
# define MEMORY_ERROR	"Unable to allocate memory."
# define UNQUOTED		"The input is quoted incorrectly."
# define ADD_LEXER_FAILED	"Failed when trying to add a new node to lexer list."


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
t_lexer	*new_lexer(char *str, t_token_type token);
void	lexer_addback(t_lexer *node);
bool	add_lexer(char *str, t_token_type token);

/*                                              tools                                                    */
// handle_error.c
int		print_error(int error_type);

# endif
