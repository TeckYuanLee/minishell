/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 22:26:14 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 17:11:18 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*newlst;

	if (!f && !del)
		return (0);
	newlst = NULL;
	while (lst)
	{
		element = ft_lstnew(f(lst->content));
		if (!element)
			ft_lstclear(&newlst, del);
		ft_lstadd_back(&newlst, element);
		lst = lst->next;
	}
	return (newlst);
}
