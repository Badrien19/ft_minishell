#include "ft_minishell.h"

#define SH_LINE_BUFFSIZE 10
#define SH_LINE_DELIM " \t\r\n\a"

char	*stradd(char *s1, char const *s2)
{
	char	*ret;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = 0;
	if (s1 != NULL)
		size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ret = malloc((sizeof(char) * (size_s1 + size_s2) + 1));
	if (ret == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		ft_memcpy(ret, s1, size_s1);
		ft_memcpy(&ret[size_s1], s2, size_s2 + 1);
		free(s1);
	}
	else
		ft_memcpy(ret, s2, size_s2 + 1);
	return (ret);
}

char	*sh_read_line(void)
{
	char	buff[SH_LINE_BUFFSIZE + 1];
	char	*str;
	size_t	ret;

	str = NULL;
	while (1)
	{
		ret = read(1, buff, SH_LINE_BUFFSIZE);
		buff[ret] = 0;
		str = stradd(str, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	return (str);
}

void    print_list(void)
{
	t_sys_infos tmp_sys_infos;
	
	tmp_sys_infos = g_sys_infos;

	if (tmp_sys_infos.list_input != NULL)
	{
		while (tmp_sys_infos.list_input->next != NULL)
		{
			printf("%s (%i) -> %p\n", tmp_sys_infos.list_input->content->value, tmp_sys_infos.list_input->content->type, tmp_sys_infos.list_input->next);
			tmp_sys_infos.list_input = tmp_sys_infos.list_input->next;
		}
		printf("%s (%i) -> %p\n", tmp_sys_infos.list_input->content->value, tmp_sys_infos.list_input->content->type, tmp_sys_infos.list_input->next);
	}
}

void	sh_pre(void)
{
	write(1, "\033[1;32m", 7);
	write(1, "minishell > ", 13);
	write(1, "\033[0m", 4);
}

void	free_list(void)
{
	t_list	*buffer;

	if (g_sys_infos.list_input == NULL)
		return ;
	buffer = g_sys_infos.list_input;
	while (buffer != NULL)
	{
		g_sys_infos.list_input = buffer;
		buffer = buffer->next;
		free(g_sys_infos.list_input->content->value);
		free(g_sys_infos.list_input->content);
		free(g_sys_infos.list_input);
	}
	g_sys_infos.list_input = NULL;
}

void	error_checker(void)
{
	t_list	*list;
	int		count_s;
	int		count_d;

	list = g_sys_infos.list_input;
	count_s = 0;
	count_d = 0;

	if (list == NULL)
		error_manager("no list_input\n");
	while (list)
	{
		if(list->content->type == single_quote)
			count_s++;
		else if(list->content->type == double_quote)
			count_d++;
		list = list->next;
	}
	printf("%i\n", count_d);
	if (count_s % 2 != 0 || count_d % 2 != 0)
		printf("quotes uneven\n");
}

int	main(int argc, char **argv)
{
	char	*user_input;
	g_sys_infos.list_input = 0;

	while (1)
	{
		sh_pre();
		user_input = sh_read_line();
		parsing(user_input);
		error_checker();
		print_list();
		free_list();
	}
	return (0);
}
