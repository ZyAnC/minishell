/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:56:17 by yzheng            #+#    #+#             */
/*   Updated: 2024/10/29 13:17:39 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if(!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
#include<stdio.h>
#include<string.h>
int main(){
 printf("%zu",strlen(((void *)0)));

}*/
