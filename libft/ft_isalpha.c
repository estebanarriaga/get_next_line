
/*
	Returns true if c is an alphabetic character (a letter).
	If islower or isupper is true of a character, then isalpha 
	is also true.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
