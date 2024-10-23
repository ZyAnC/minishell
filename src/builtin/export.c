#include "./minishell.h"

void bubble_sort(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (env[j][0] > env[j + 1][0])
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char **sort_env()
{
	char	**env_copy;
	int		count;

	count = 0;
	while (ms()->env[count])
		count++;
	env_copy = malloc(count * sizeof(char *));
	for (int i = 0; i < count; i++) {
		env_copy[i] = ms()->env[i];
	}
	bubble_sort(env_copy, count);
	return(env_copy);
}


// int	ft_valid_character(char *str)
// {
// 	int	i;
// 	int	flag;

// 	flag = 1;
// 	i = 0;
// 	if (!str)
// 		return (1);
// 	while(str[i])
// 	{
// 		if ((str[i] >= 'A' && str[i] <= 'Z')
// 		|| (str[i] >= 'a' && str[i] <= 'z')
// 		|| str[i] == '_'
// 		|| (str[i] >= '0' && str[i] <= '9'))
// 		{
// 			i++;
// 		}
// 		else
// 		{
// 			flag = 0;
// 			break;
// 		}
// 	}
// 	free(str);
// 	return(flag);
// }

// void		update_env(int	i, char	*str)
// {
// 	free(ms()->env[i]);
// 	ms()->env[i] = ft_strdup(str);
// //	tmp->content = ft_strdup(str);
// }

void	add_env(char	*str)
{
//	t_list	*new;
	int		i;
	int		j;

	// new = ft_lstnew(str);
	// ft_lstadd_back(&ms()->env_list, new);
	i = 0;
	while(ms()->env[i])
		i++;
	char **new_env = malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
		restart(1);
	j = -1;
	while (++j < i)
		new_env[j] = ms()->env[j];
	new_env[i] = ft_strdup(str);
	new_env[i+1] = NULL;
	if (new_env[i] == NULL)
		restart(1);
	free(ms()->env);
	i  = 0;
	while(new_env[i])
	{
		ms()->env[i] = ft_strdup(new_env[i]);
		if(!ms()->env[i])
			restart(1);
		i++;
	}
	free(new_env);
}

void	update_or_add_envs(char	*str)
{
	int		i;
	char	*name;
	int		size;
//	t_list* tmp;

//	tmp = ms()->env_list;
	size = 0;
	while(str[size] != '=')
		size++;
	name = ft_strndup(str,size);
	i = 0;
	while (ms()->env[i] && !ft_strnstr(ms()->env[i], name, size))
			i++;
	// while(tmp && !ft_strnstr(tmp->content, name, size))
	// 	tmp = tmp->next;
	if(!ms()->env[i])
		add_env(str);
	else
	{
		free(ms()->env[i]);
		ms()->env[i] = ft_strdup(str);
	}
//		update_env(i, str,tmp);
	free(name);
}

/*
	Different cases:
	case 1: export
	case 2: export name=aaa echo a
	case 3: export name= aaa
	case 4: export 1name=aaa

	case 1: no argument after export
		intput: export
		output: it will show all the enviroment variable list.
		exit_code: 0
	case 2: extra infos after the valid defination
		intput: export name=aaa echo a
		output:no output(but it will add name=aaa to enviroment variable list and envs.)
		exit_code: 0
	case 3: there is a space between variable value and '='
		input: export name= aaa
		output: no output (but it will add name= to enviroment variable list and envs.)
		exit_code: 0
	case 4: the variable name is invalid
		input: export 1name=aaa
		output:bash: export: `1name=aaa': not a valid identifier
		exit_code: 1
*/
int	ft_export(char	**cmd)
{
	if (!cmd[1])
		return(print_sorted_env());// sorted function is not correct
	if (!is_defining_var(cmd[1]))
	{
		export_err(cmd[1]);
		ms()->exit = 1;
	}
	add_node_to_list(&ms()->env_list, cmd[1]);
	update_or_add_envs(cmd[1]);
	ms()->exit = 0;
	return (1);
}

// char	*lastequal(char	*str)
// {
// 	int length;
// 	char *last_equal;
// 	char *result;
// 	last_equal = ft_strrchr(str, '=');
// 	if (last_equal != NULL)
// 	{
// 		length = last_equal - str;
// 		result = malloc(length + 1);
// 		if (result == NULL)
// 		{
// 			perror("Failed to allocate memory");
// 			return(NULL);
// 		}
// 		strncpy(result, str, length);
// 		result[length] = '\0';
// 	}
// 	else
// 		return(NULL);
// 	return (result);
// }
// int	ft_export(char	**cmd)
// {
// 	int	i;
// 	int	status;

// 	i = 1;
// 	status = 1;
// 	if (!cmd[1])
// 		return(print_sorted_env());
// 	while(cmd[i])
// 	{
// 		if ((cmd[i][0] >= 'A' && cmd[i][0] <= 'Z')
// 		|| (cmd[i][0] >= 'a' && cmd[i][0] <= 'z') || cmd[i][0] == '_')
// 		{
// 			if (!ft_valid_character(lastequal(cmd[i])))
// 				status = export_err(cmd[i]);
// 			else
// 				update_or_add(cmd[i]);
// 		}
// 		else
// 			status = export_err(cmd[i]);
// 		i++;

// 	}
// 	if (status)
// 		ms()->exit = 0;
// 	return (1);
// }


