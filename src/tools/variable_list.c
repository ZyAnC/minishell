/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:56:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/15 11:31:10 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_variable(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	return (new);
}

/*
	@Why "return(ft_strdup(""))"?
	return(ft_strdup("")) and return (NULL) are both return a NULL, but using
	former one, it will generate a memoery for it. In other function, we need
	free the memory we allocate for env_value, so if we just return a NULL with
	out allocating memory for it, it will generate an error.
*/
char	*get_variable_value(char *env_name)
{
	t_env	*env;
	t_list	*tmp;

	if (env_name[0] == '$')
		env_name++;
	tmp = ms() ->env_list;

	while (tmp && env_name)
	{
		env = (t_env *)(tmp->content);
		if (!ft_strcmp(env->name, env_name))
			return (ft_strdup(env->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

/*
	@function
	The funtion will loop the env list to find if any env.name matching with passed name.

	@return
	return the env if found matched one;
	return NULL, if did NOT find matched one;
*/
static t_env	*find_variable(t_list *list, char *name)
{
	t_env	*env;

	if (!list)
		return (NULL);
	while (list)
	{
		env = list->content;
		if (!ft_strcmp(env->name, name))
			return (env);
		list = list->next;
	}
	return (NULL);
}

void	add_node_to_list(t_list **list, char *str)
{
	char	*name;
	char	*value;
	int		i;
	t_env	*env;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break;
	}
	name = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	env = find_variable(*list, name);
	if (env)
	{
		free(name);
		free(env->value);
		env->value = value;
	}
	else
		ft_lstadd_back(list, ft_lstnew(new_variable(name, value)));
}
