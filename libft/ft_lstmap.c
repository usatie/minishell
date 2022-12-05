/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:47:49 by susami            #+#    #+#             */
/*   Updated: 2022/04/24 07:14:45 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: protected (Empty list can be mapped to empty list)
// f: not protected
// del: not protected
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*ptr;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	lst = lst->next;
	if (new == NULL)
		return (NULL);
	ptr = new;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (new->next == NULL)
		{
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (ptr);
}
