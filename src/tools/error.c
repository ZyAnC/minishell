/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:02:58 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/04 19:20:54 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	open_error(char *message)
{
	if (!access(message, F_OK))
		ex_error(message, PREMISSON, 126);
	else
		ex_error(message,NFILE,2);
	restart(0);
}

void	ex_error(char *message, t_error type, int err_status)
{
	ft_putstr_fd("minishell: ", 2);
	if(message)
		ft_putstr_fd(message, 2);
	if (type == DIRECTORY)
		ft_putstr_fd(" : Is a directory", 2);
	else if (type == COMMAND)
		ft_putstr_fd(" : command not found", 2);
	else if  (type == NFILE)
		ft_putstr_fd(" : No such file or directory", 2);
	else if  (type == PREMISSON)
		ft_putstr_fd("Permission denied", 2);
	else if  (type == FORK)
		ft_putstr_fd(" : fork failed", 2);
	else if  (type == PIPE)
		ft_putstr_fd(" : pipe failed", 2);
	else if  (type == ERR)
		ft_putstr_fd(strerror(errno), 2);
	else if  (type == TOOMUCH)
		ft_putstr_fd(" : too many arguments", 2);
	else if  (type == HOME)
		ft_putstr_fd(" : HOME not set", 2);
	ft_putchar_fd('\n', 2);
	ms()->exit = err_status;
}

int	export_err(char	*cmd)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ms()->exit = 1;
	return (0);
}

int	print_sorted_env()
{
	int	i;
	int	j;
	char	**envsort;

	i = 0;
	j = 0;
	envsort = sort_env();
	while (ms()->env[i])
	{
		j = 0;
		printf("declare -x ");
		while(envsort[i][j] != '=')
			printf("%c",envsort[i][j++]);
		j++;
		printf("=\"");
		while(envsort[i][j])
			printf("%c",envsort[i][j++]);
		printf("\"\n");
		i++;
	}
	free(envsort);
	return(1);
}
