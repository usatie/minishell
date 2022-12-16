/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:26:48 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 09:27:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include "minishell.h"

int	ft_pwd(char *argv[])
{
	char		cwd[PATH_MAX];
	struct stat	st1;
	struct stat	st2;
	char		*pwd;

	(void)argv;
	pwd = getenv("PWD");
	if (pwd)
	{
		bzero(&st1, sizeof(struct stat));
		bzero(&st2, sizeof(struct stat));
		stat(".", &st1);
		stat(pwd, &st2);
		if (st1.st_ino == st2.st_ino)
		{
			printf("%s\n", pwd);
			return (0);
		}
	}
	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
