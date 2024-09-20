/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:46 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/14 17:48:29 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*getnewline(char *storage);
char	*fft_strjoin(char *s1, char *s2);
char	*fft_strchr( char *s, int c);
char	*ft_getline(char *src);
size_t	fft_strlen(const char *str);
char	*ft_free(char **str);

#endif
