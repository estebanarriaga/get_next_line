
/*
	The function ft_striteri() applies the function f() given
	as a parameter inside 's' and in the pointer direction.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	s_len;

	if (s)
	{
		s_len = ft_strlen(s);
		while (s_len --)
		{
			f(s_len, &s[s_len]);
		}
	}
}
