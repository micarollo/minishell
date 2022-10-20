#include "../../include/minishell.h"

/**
 * Function that creates a new char* cleaned of quotes 
*/
char	*quotes_clean(t_token *new)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	clean = ft_calloc((ft_strlen(new->str) + 1), sizeof(char));
	if (!clean)
		return (NULL);
	while(new->str[i])
	{
		j = i;
		while(new->str[i] && new->str[i] != '\'' && new->str[i] != '\"')
			i++;
		ft_strlcat1(clean, &new->str[j], ft_strlen(clean) + i - j + 1);
		if(!new->str[i])
			return (clean);
		j = i++;
		while(new->str[i] && new->str[i] != new->str[j])
			i++;
		ft_strlcat1(clean, &new->str[j+1], ft_strlen(clean) + i++ - j);
	}
	return (clean);
}

/**
 * Function that frees initial str of token with quotes and also elimiates excessive memory in char* from quotes_clean
*/
void	quotes_update(t_token *new)
{
	int	i;
	char	*temp;

	i = 0;
	temp = new->str;
	new->str = quotes_clean(new);
	free(temp);
	temp = new->str;
	new->str = ft_strdup(new->str);
	free(temp);
}



size_t	ft_strlcat1(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	length;

	i = 0;
	j = ft_strlen(dst);
	length = ft_strlen(dst) + ft_strlen(src);
	while (src[i] && j < dstsize - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (length);
}