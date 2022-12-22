/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:56:48 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 19:16:00 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*new_tmp;

	if (lst == NULL)
		return ;
	new = *lst;
	while (new != NULL)
	{
		new_tmp = new->next;
		ft_lstdelone(new, del);
		new = new_tmp;
	}
	*lst = NULL;
}
