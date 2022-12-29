/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:25:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/29 16:58:52 by susami           ###   ########.fr       */
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

static bool	is_identifier(char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

// Assignment string should be allocated and should not be freed.
static int	export_single_assignment(char *string)
{
	char	*name;
	char	*name_end;

	// export name
	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		if (!is_identifier(string))
		{
			free(string);
			ft_custom_perror("export", "not a valid identifier");
			return (-1);
		}
		// If already exists, do nothing
		if (ft_getenv(string))
		{
			free(string);
			return (0);
		}
		// If not exists, add to nameonly environ
		putenv_name(string);
		return (0);
	}
	// export name=value
	name = ft_strndup(string, name_end - string);
	if (!is_identifier(name))
	{
		free(string);
		free(name);
		ft_custom_perror("export", "not a valid identifier");
		return (-1);
	}
	if (name == NULL)
		fatal_exit("ft_strndup");
	unsetenv_name(name);
	free(name);
	if (ft_putenv(string) < 0)
		fatal_exit("ft_putenv");
	return (0);
}

static int	export_all(char **argv)
{
	char	*assignment;
	bool	error;
	int		i;

	error = false;
	i = 1;
	while (argv[i])
	{
		assignment = ft_strdup(argv[i]);
		if (assignment == NULL)
			fatal_exit("ft_strdup");
		if (export_single_assignment(assignment) < 0)
			error = true;
		i++;
	}
	if (error)
		return (-1);
	return (0);
}

int	ft_export(char **argv)
{
	if (argv[1] == NULL)
		print_all_variables();
	else
	{
		if (export_all(argv) < 0)
			return (1);
	}
	return (0);
}
