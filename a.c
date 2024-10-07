
#include "./include/minishell.h"


t_ms    *ms(void)
{
	static t_ms ms;
	return(&ms);
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
int main(int ac,char **av,char **env)
{

	int i = 0;
	char	*str="Yan=yy";
	while(str[i] != '=')
		i++;

	printf("%s\n",ft_strndup(str,i));
}
