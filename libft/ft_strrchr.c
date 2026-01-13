
/*
	The strchr() function locates the first occurrence of c (converted to a 
	char) in the string pointed to by s.  The terminating null character
	is considered to be part of the string; therefore if c is '\0', the
	functions locate the terminating '\0'.

	The functions strchr() returns a pointer to the located character,
	or NULL if the character does not appear in the string.

	The strrchr() function is identical to strchr(),
	except it locates the last occurrence of c.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*cs;
	char	ch;

	ch = c;
	cs = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (cs[len] == ch)
			return ((char *)cs + len);
		len--;
	}
	return (0);
}
