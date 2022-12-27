/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:25:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 17:31:21 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	print_all_variables(void)
{
	int		i;

	i = 0;
	while (g_env.environ[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(g_env.environ[i], STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (g_env.environ_name[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(g_env.environ_name[i], STDOUT_FILENO);
		i++;
	}
}

// Assignment string should be allocated and should not be freed.
static void	export_single_assignment(char *string)
{
	char	*name;
	char	*name_end;

	// export name
	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		// If already exists, do nothing
		if (ft_getenv(string))
		{
			free(string);
			return ;
		}
		// If not exists, add to nameonly environ
		putenv_name(string);
		return ;
	}
	name = ft_strndup(string, name_end - string);
	if (name == NULL)
		fatal_exit("ft_strndup");
	unsetenv_name(name);
	free(name);
	// export name=value
	if (ft_putenv(string) < 0)
		fatal_exit("ft_putenv");
	return ;
}

static void	export_all(char **argv)
{
	char	*assignment;
	int		i;

	i = 1;
	while (argv[i])
	{
		assignment = ft_strdup(argv[i]);
		if (assignment == NULL)
			fatal_exit("ft_strdup");
		export_single_assignment(assignment);
		i++;
	}
}

int	ft_export(char **argv)
{
	if (argv[1] == NULL)
		print_all_variables();
	else
		export_all(argv);
	return (0);
}
