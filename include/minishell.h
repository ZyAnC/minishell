/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:00:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/04 19:48:04 by yzheng           ###   ########.fr       */
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
# include <sys/stat.h>
/*For global*/
t_ms	*ms(void);

/*For error*/
int	export_err(char	*cmd);
void	open_error(char *message);
void	ex_error(char *message, t_error type, int err_status);
/*For shell*/
void	restart(int exit);
void	test();
/*For	tools*/
void	close_inout();
void	pp_free(char **fly);
void	close_all(int	prev_fd);
void	check_infile(t_cmd *cm);
char	*ft_strndup(char *src, int size);
char *replace_first_substring(char *str, char *old_sub, char *new_sub);
int	ft_strcmp(char *s1, char *s2);
void	set_fd(t_cmd *cm);
/*For execute*/
/*<-----pipe && redirect----->*/

pid_t	exe_pipe(t_cmd *cm);
pid_t	exe_pipe2(t_cmd *cm);
pid_t	exe_pipe3(t_cmd *cm);
void	type_hdoc(t_cmd *cm);
pid_t	type_outpipe(t_cmd *cm, int	*prev_fd);
/*<-----exe----->*/
char	*findvalidcmd(char **shellcmd);
void	real_execute(t_cmd *cm);
int		ft_env(void);
/*<-----builtin----->*/
int	ft_cd(char **cmd);
int	ft_env(void);
int	ft_unset(char **cmd);
int	ft_echo(char	**cmd);
void	ft_exit(char **cmd);
int	ft_export(char	**cmd);
int	print_sorted_env();
char **sort_env();
char	*get_env(char	*name);
# endif

