

/*
	The function ft_split() a string and a character that is
	going to work as a separator.
	
	The function returns an array of strings resulting from the
	separation if the given string separated by the given character
	
	The character that works as a delimiter is not included in the
	resulting strings
*/

#include "libft.h"

static char	**ft_mem_alloc(const char *s, char c)
{
	int		i;
	char	**s_malloc;
	int		arr_num;

	i = 0;
	arr_num = 0;
	if (*s && s[0] != c)
		arr_num++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			arr_num++;
		i++;
	}
	s_malloc = (char **)malloc((arr_num + 1) * sizeof(char *));
	if (!s_malloc)
		return (0);
	return (s_malloc);
}

static void	ft_free(char **str_arr)
{
	int	i;

	i = 0;
	if (str_arr != 0)
	{
		while (str_arr[i] != 0)
		{
			free(str_arr[i]);
			i ++;
		}
		free(str_arr);
	}
}

static char	**ft_split_aux(char **res, char const *s, char c, int arr_count)
{
	int		current;
	int		last;

	current = 0;
	last = 0;
	while (s[current])
	{
		while (s[current] == c)
			current ++;
		last = current;
		while (s[current] && s[current] != c)
			current ++;
		if (current > last)
		{
			res[arr_count] = ft_substr(s, last, current - last);
			if (!res[arr_count])
			{
				ft_free(res);
				return (0);
			}
			arr_count ++;
		}
	}
	res[arr_count] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		arr_count;

	if (!s)
		return (0);
	res = ft_mem_alloc(s, c);
	if (!res)
		return (0);
	arr_count = 0;
	res = ft_split_aux(res, s, c, arr_count);
	if (!res)
		return (0);
	return (res);
}
