#include "ft_minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static char		**free_mllc(char **splitted, size_t k)
{
	size_t i;

	i = -1;
	while (++i > k)
		free(splitted[i]);
	free(splitted);
	return (0);
}

static size_t	nbr_str(char const *s, char c)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	start;
	char	**splitted;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	if (!(splitted = (char**)malloc(sizeof(char*) * (nbr_str(s, c) + 1))))
		return (NULL);
	while (s[i] && k < (nbr_str(s, c)))
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (!(splitted[k] = malloc(sizeof(char) * ((i - start) + 1))))
			return (free_mllc(splitted, k));
		ft_strlcpy(splitted[k], &s[start], i - start + 1);
		k++;
	}
	splitted[k] = NULL;
	return (splitted);
}