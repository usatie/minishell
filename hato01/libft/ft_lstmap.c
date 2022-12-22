/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:24:40 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/02 23:03:52 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*ans_lst;
	t_list	*new_node;

	if (lst == NULL || f == NULL)
		return (NULL);
	ans_lst = NULL;
	while (lst != NULL)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (new_node == NULL)
		{
			ft_lstclear(&ans_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&ans_lst, new_node);
		lst = lst->next;
	}
	return (ans_lst);
}
