/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:32:18 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:32:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_node(t_node *node)
{
	if (!node)
		return ;
	free_node(node->next);
	free_node(node->lhs);
	free_node(node->rhs);
	free_node(node->args);
	free_node(node->redirects);
	free(node);
}
