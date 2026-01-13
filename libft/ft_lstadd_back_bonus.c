
/*
	The fuction ft_lstadd_back() adds the node 'new'
	at the end of the list 'lst'
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add;

	if (lst)
	{
		if (*lst)
		{
			add = ft_lstlast(*lst);
			add -> next = new;
		}
		else
			*lst = new;
	}
}
