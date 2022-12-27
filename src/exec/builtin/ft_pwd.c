/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:48 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 09:26:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static bool	is_pwd_valid(char *pwd);

int	ft_pwd(char *argv[])
{
	char		cwd[PATH_MAX];
	char		*pwd;

	(void)argv;
	pwd = ft_getenv("PWD");
	if (pwd && is_pwd_valid(pwd))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	ft_perror("pwd");
	return (1);
}

static bool	is_pwd_valid(char *pwd)
{
	struct stat	st1;
	struct stat	st2;

	ft_bzero(&st1, sizeof(struct stat));
	ft_bzero(&st2, sizeof(struct stat));
	stat(".", &st1);
	stat(pwd, &st2);
	if (st1.st_ino == st2.st_ino)
		return (true);
	return (false);
}
