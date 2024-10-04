
#include "./include/minishell.h"


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	slen;

	if (!*to_find)
		return ((char *)str);
	i = 0;
	slen = ft_strlen(str);
	if (len > slen)
		len = slen;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j < len))
			j++;
		if (!to_find[j])
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
	{
		return (ft_strlen(src));
	}
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}


size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = 0;
	j = 0;
	result = 0;
	while (dest[i] != '\0')
		i++;
	while (src[result] != '\0')
		result++;
	if (size <= i)
		result += size;
	else
		result += i;
	while (src[j] != '\0' && (i + 1) < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (result);
}



char	*ft_strndup(char *src, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);

	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char *replace_first_substring(char *str, char *old_sub, char *new_sub)
{
	char	*result;
	char	*pos;
	int		new_len;
	int		old_len;

	new_len = ft_strlen(new_sub);
	old_len = ft_strlen(old_sub);
	pos = ft_strnstr(str, old_sub, ft_strlen(str));
	result = (char *)malloc(ft_strlen(str) - old_len + new_len + 1);
	if (!result)
		return NULL;
	ft_strlcpy(result, str, pos - str + 1);
	result[pos - str] = '\0';
	ft_strlcat(result, new_sub, ft_strlen(result) + new_len + 1);
	ft_strlcat(result, pos + old_len, ft_strlen(result) + ft_strlen(pos + old_len) + 1);
	return result;
}
char	*replace_env(char	*envname, char *src)
{
	int	i;
	int	j;
	char	*dest;
	char	*replacement;

	replacement = NULL;
	i = 1;
	j = 0;
	while(isprint(envname[i]) && envname[i] != ' ' && envname[i] != '\0')
		i++;
	dest = ft_strndup(envname, i);
	if (dest == NULL)
		return (NULL);
	while (ms()->env[j] && !ft_strnstr(ms()->env[j], dest+1, i - 1))
		j++;
	if(!ms()->env[j])
		replacement = "";
	else
		replacement = ms()->env[j] + i;
	dest = replace_first_substring(src,dest, replacement);

	return(dest);
}


t_ms    *ms(void)
{
	static t_ms ms;
	return(&ms);
}

int main(int ac,char **av,char **env)
{
	char *doc = "$ nihao $HOME  haha";
char	*dc;
	ms()->env = env;
	int i = 0;

	while(doc[i])
	{
		dc = ft_strchr(doc + i,'$');
		printf("dc:%s\n",dc);
		if (dc && *(dc + 1) && *(dc + 1) != '\n' && *(dc + 1) != ' ')
		{
			doc = replace_env(dc, doc);
			i = 0;
		}
		printf("doc:%s\n",doc);
		i++;
	}
	printf("%s\n",doc);
}
