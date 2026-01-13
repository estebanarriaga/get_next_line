
/*
	The function ft_lstmap() iterates the list 'lst' and applies the function f()
	to the content of each node. It creates a new list from the correct application
	of the function f() in each node.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst -> content));
	if (!new)
		return (NULL);
	start = new;
	lst = lst -> next;
	while (lst)
	{
		new -> next = ft_lstnew(f(lst -> content));
		if (!new)
			return (NULL);
		lst = lst -> next;
		new = new -> next;
	}
	return (start);
}
