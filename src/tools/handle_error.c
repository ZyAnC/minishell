/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:22:37 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/26 12:40:15 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	print_error(char *err_type, int err_fd)
{
	ft_putchar_fd(err_type, STDERR_FILENO);
	ms() ->exit = err_fd;
	return (false);
}

