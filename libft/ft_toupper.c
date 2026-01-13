
/*
	The ft_toupper() function converts a lower-case letter to the corresponding
	upper-case letter.
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
