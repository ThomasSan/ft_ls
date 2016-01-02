/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/02 17:55:14 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

void	ft_init_option(t_opt *opt)
{
	opt->opt_a = 0;
	opt->opt_l = 0;
	opt->opt_r = 0;
	opt->opt_t = 0;
	opt->opt_rec = 0;
}

void	displaytab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("tab = %s\n", tab[i]);
		i++;
	}
}

int		main(int ac, char **av)
{
	int				i;
	int				files;
	char			**tab;
	DIR				*dirp;
	struct dirent	*dp;
	t_opt			opt;

	i = 1;
	files = 0;
	ft_init_option(&opt);
	files =	ft_parseoption(ac, av, &opt);
	tab = (char **)malloc(sizeof(char *) * (files + 1));
	ft_filesintab(ac, av, tab);
	printf("tab before sort\n");	
	displaytab(tab);
	ft_sorttab(tab, files);
	printf("tab after sort\n");	
	displaytab(tab);
	while (i < files)
	{
		if (ac == 1)
			dirp = opendir(".");
		else
			dirp = opendir(tab[i]);
		if (dirp == NULL)
		{
			ft_errordir(tab[i]);
			return (0);
		}
		while ((dp = readdir(dirp)) != NULL)
		{
			if (opt.opt_l == 1)
				ft_inspect_file(dp->d_name);
			ft_putendl(dp->d_name);
		}
		closedir(dirp);
		i++;
	}
	free(tab);
	return (0);
}
