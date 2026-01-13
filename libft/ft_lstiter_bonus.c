
/*
	The function ft_lstiter() iterates the list 'lst' and applies
	the function f() on the content of each node
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iter;

	if (lst)
	{
		while (lst)
		{
			iter = lst -> next;
			f(lst -> content);
			lst = iter;
		}
	}
}
