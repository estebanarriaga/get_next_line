
/*
	Returns true if c is a 7-bit unsigned char value that
	fits into the ASCII character set.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
