/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:23:30 by yzheng            #+#    #+#             */
/*   Updated: 2024/09/24 11:17:46 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ms	*ms(void)
{
	static t_ms ms;
	return(&ms);
}

char	*prompt()
{
	char	*str;
	char	*str2;

	str = ft_strjoin("minishell:" , ms()->cwd);
	if (!str)
		return(NULL);
	str2 = ft_strjoin(str,"$ ");
	if (!str2)
	{
		free(str);
		return(NULL);
	}
	free(str);
	return(str2);

}
void	buildshell()
{
	while (1)
	{
		ms()->prompt = prompt();
		ms()->input = readline(ms()->prompt);
		ms()->lines++;
		if(!ms()->input)
		{
			ft_printf("exit\n");
			restart(1);
		}
		add_history(ms()->input);
		if (!pre_handler());
			return_error // unfinished
		execute_the_cmd// unfinished
		restart(0);
	}
	rl_clear_history();
}

static void init_ms()
{
	ft_bzero(ms(),sizeof(t_ms));
	ms()->exit = 0;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ms()->cwd = getcwd(NULL, 2048);
	if(!(ms()->cwd))
	{
		perror("getcwd() error");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	if (ac != 1)
	{
		ft_putstr_fd("Too many arguments\n",2);
		exit(127);
	}
	(void)av;
	init_ms();

	buildshell();
	return (0);
}
