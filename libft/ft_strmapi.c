
/*
	ft_strmapi() applies the function f() to each character of 's'.
	f() receives as a parameter the current position of the string and the
	character in that position.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	s_len;
	int		i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	newstr = (char *)malloc(s_len + 1);
	if (!newstr)
		return (0);
	i = 0;
	while (i < (int)s_len)
	{
		newstr[i] = f(i, (char)s[i]);
		i ++;
	}
	newstr[i] = 0;
	return (newstr);
}
