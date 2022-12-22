/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:33:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:32:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	free_redirect(t_redirect *redirect);
static void	free_argv(char **argv);

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free_pipeline(pipeline->next);
	free_redirect(pipeline->redirects);
	free_argv(pipeline->argv);
	free(pipeline);
}

static void	free_redirect(t_redirect *redirect)
{
	if (!redirect)
		return ;
	free_redirect(redirect->next);
	if (redirect->path)
		free(redirect->path);
	if (redirect->delimiter)
		free(redirect->delimiter);
	free(redirect);
}

static void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
