/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:32:01 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:32:03 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_tok(t_token *tok)
{
	if (!tok)
		return ;
	free_tok(tok->next);
	free_str(tok->str);
	free(tok);
}
