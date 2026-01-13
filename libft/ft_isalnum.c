
/*
	Returns true if c is an alphanumeric character (a letter or number); 
	in other words, if either isalpha or isdigit is true of a character, 
	then isalnum is also true.
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	else
		return (0);
}
