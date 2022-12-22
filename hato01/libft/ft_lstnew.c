/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <mkunimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:57:04 by mkunimot          #+#    #+#             */
/*   Updated: 2022/02/27 14:07:41 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ans;

	ans = (t_list *)malloc(sizeof(t_list));
	if (ans == NULL)
		return (NULL);
	ans->content = content;
	ans->next = NULL;
	return (ans);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	puts("----ft_lstnew------");
	char	test11[] = "12345";
//	char	test21[] = "abcde";
//	char	test31[] = "123\n";

	t_list	*ans = ft_lstnew(test11);
	
	while ()
	{
		t_list	*p;
		p = ans.next;
		printf("%s",ans.next);

}
*/
