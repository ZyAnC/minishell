/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
<<<<<<< HEAD:include/minishell.h
/*   Updated: 2024/09/20 11:23:27 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft/libft.h"
# include "../libft/printf/printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "structs.h"

# endif
=======
/*   Updated: 2024/09/20 12:01:06 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SHELL_H
# define SHELL_H
#include "../libft/libft/libft.h"
#include "../libft/printf/printf.h"
#include "../libft/get_next_line/get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_ms
{
   int	in_fd;
   int	out_fd;
   int	exit;
   int	lines;
   char	*cwd;
   char	*prompt;
   char	*input;
}   t_ms;
  
# endif
>>>>>>> b6b61a2 (yan):include/shell.h
