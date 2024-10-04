

#include "minishell.h"

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

		if (pre_handle())
			exe(ms()->cmds);
		restart(0);
	}
}

char	*findpath(char **env)
{

	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	return (env[i]);

}

t_list *get_env_list(char **env)
{
	t_list *env_list = NULL;
	int i = 0;

	while (env[i])
	{
		char *env_copy = ft_strdup(env[i]);
		if (!env_copy)
			return (NULL);
		t_list *new_node = ft_lstnew(env_copy);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

static void init_ms(char **env)
{

	ft_bzero(ms(),sizeof(t_ms));
	ms()->exit = 0;
	ms()->in_fd = STDIN_FILENO;
	ms()->out_fd = STDOUT_FILENO;
	ms()->hfd = -1;
	ms()->cwd = getcwd(NULL, 2048);
	ms()->path = findpath(env);
	ms()->env_list = get_env_list(env);
	ms()->env = env;
	ms()->fd[0] = -1;
	ms()->fd[1] = -1;
	ms()->tokens = NULL;

	if(!(ms()->cwd))
	{
		perror("getcwd() error");
		exit(1);
	}
}

int main(int  ac, char **av, char **env)
{
	if (ac != 1)
	{
		ft_putstr_fd("Too many arguments\n",2);
		exit(127);
	}
	(void)av;
	init_ms(env);
	buildshell();
	return (0);
}

