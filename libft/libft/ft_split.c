/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:50:46 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/04 10:39:36 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int	countstring(char *str, char charset)
{
	int	i;
	int	count;
	int	isprevsep;

	i = 0;
	count = 0;
	isprevsep = 1;
	while (str[i])
	{
		if (str[i] == charset)
		{
			isprevsep = 1;
		}
		else if (isprevsep)
		{
			count++;
			isprevsep = 0;
		}
		i++;
	}
	return (count);
}

static int	sp(char **result, char *str, char charset, int j)
{
	t_ParseContext	ctx;
	int				i;

	i = 0;
	ctx.result = result;
	ctx.str = str;
	ctx.charset = charset;
	ctx.i = &i;
	ctx.j = &j;
	if (!result || !str)
		return (-1);
	if (!process_string(&ctx))
		return (0);
	result[j] = NULL;
	return (1);
}

char	**ft_split(char *str, char charset)
{
	char	**result;
	int		size;

	if (!str)
		return (NULL);
	size = countstring(str, charset);
	result = malloc((size + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (sp(result, str, charset, 0))
		return (result);
	else
		return (NULL);
}
