#include "ft_minishell.h"

static char	**free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (0);
}

static int	motcounter(const char *str, char charset)
{
	int	i;
	int	mot;
	int	motcount;

	motcount = 0;
	mot = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == charset)
		{
			if (mot++ == 0)
				motcount++;
		}
		else
			mot = 0;
		i++;
	}
	if (mot == 0)
		motcount++;
	return (motcount);
}

static char	*fill(const char *str, char charset, int *i)
{
	char	*tmp;
	int		y;

	y = 0;
	while (str[*i] == charset && str[*i] != '\0')
		(*i)++;
	while ((str[(*i) + y] != charset) && str[(*i) + y] != '\0')
		y++;
	tmp = malloc(sizeof(char) * (y + 1));
	if (tmp == 0)
		return (NULL);
	y = 0;
	while ((str[*i] != charset) && str[*i] != '\0')
		tmp[y++] = str[(*i)++];
	tmp[y] = '\0';
	return (tmp);
}

char	**ft_split(const char *str, char charset)
{
	int		wordcount;
	char	**tab;
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	wordcount = motcounter(str, charset);
	tab = malloc(sizeof(char *) * wordcount + 1);
	if (tab == 0)
		return (0);
	while (wordcount > 0)
	{
		tab[x++] = fill(str, charset, &i);
		if (tab[x - 1] == NULL)
			return (free_all(tab));
		wordcount--;
	}
	tab[x] = 0;
	return (tab);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	size_t i;
	size_t size_s;

	i = 0;
	size_s = ft_strlen(s);
	while (i < size_s)
	{
		if (c == s[i])
			return (char*)(&s[i]);
		i++;
	}
	if (c == s[i])
		return (char*)(&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;
	size_t	size_s1;

	i = -1;
	size_s1 = ft_strlen(s1);
	if (!(copy = malloc((sizeof(char) * size_s1) + 1)))
		return (NULL);
	while (++i < size_s1)
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}

char		*ft_strndup(const char *s1, int n)
{
	char	*dup;
	int		i;
	int		size_s1;

	i = 0;
	size_s1 = (int)ft_strlen(s1);
	if ((n > size_s1))
		n = size_s1;
	if (!(dup = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (!(ret = malloc((sizeof(char) * (size_s1 + size_s2) + 1))))
		return (NULL);
	ft_memcpy(ret, s1, size_s1);
	ft_memcpy(&ret[size_s1], s2, size_s2 + 1);
	return (ret);
}

void	ft_putstr(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (s1[0] == '\0' || s2[0] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (s1[0] == '\0' || s2[0] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		if (!s1[i] && s2[i])
			return (-1);
		if (s1[i] && !s2[i])
			return (-1);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
