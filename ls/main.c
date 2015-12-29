/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/29 18:49:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include "ft_ls.h"

void	ft_usage(void)
{
	ft_putstr("ft_ls : illegal option --");
	ft_putchar('\n');
	ft_putstr("usage : ft_ls : [-Rlart] [file ..]i\n");
}

void	ft_errordir(char *s)
{
		ft_putstr("ft_ls: ");
		ft_putstr(s);
		ft_putendl(": No such file or directory");
}

int		main(int ac, char **av)
{
	(void)ac;
	DIR *dirp;
	struct dirent *dp;

	if (ac == 1)
		dirp = opendir(".");
	else
		dirp = opendir(av[1]);
	if (dirp == NULL)
	{
		ft_errordir(av[1]);
		return (0);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_inspect_file(dp->d_name);
		ft_putendl(dp->d_name);
	}
	closedir(dirp);
	return (0);
}
