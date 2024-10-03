/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 07:56:08 by jingwu            #+#    #+#             */
/*   Updated: 2024/10/03 09:28:03 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ft_strdup(""));
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
char	*get_env_value(char *env_name)
{
	t_env	*env;
	t_list	*tmp;

	if (env_name[0] == '$')
		env_name++;
	tmp = ms() ->env_list;
	while (tmp)
	{
		env = (t_env *)(tmp->content);
		if (!ft_strcmp(env->name, env_name))
			return (ft_strdup(env->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));// why can't return NULL here????
}

void	add_env_node(t_list **list, char *str)
{
	char	*name;
	char	*value;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break;
	}
	name = ft_substr(str, 0, i);
	value = get_env_value(name);
	if (!value)
	{
		value = ft_strdup(str + i + 1);
		ft_lstadd_back(list, ft_lstnew(new_env(name, value)));
	}
	else
		free(name);
}
