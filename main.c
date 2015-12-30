/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/30 18:50:17 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include "ft_ls.h"

void	ft_usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-Rlart] [file ..]\n");
}

void	ft_errordir(char *s)
{
	ft_putstr("ft_ls: ");
	perror(s);
}

int		main(int ac, char **av)
{
	int				i;
	DIR				*dirp;
	struct dirent	*dp;
	t_opt			*opt = NULL;

	i = 1;
	ft_parseoption(ac, av, opt);
	if (ac == 1)
		dirp = opendir(".");
	while (ac > 1)
	{
		if(ac != 1)
		dirp = opendir(av[i]);
		if (dirp == NULL)
		{
			ft_errordir(av[i]);
			return (0);
		}
		while ((dp = readdir(dirp)) != NULL)
		{
			ft_inspect_file(dp->d_name);
			ft_putendl(dp->d_name);
		}
		closedir(dirp);
		i++;
		ac--;
	}
	return (0);
}
