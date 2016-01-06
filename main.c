/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/06 17:15:54 by tsanzey          ###   ########.fr       */
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

void	ft_init_list(t_lst *l)
{
	l->name = NULL;
	l->right[0] = 0;
	l->uid = NULL;
	l->gid = NULL;
	l->time = NULL;
	l->links = 0;
	l->size = 0;
	l->next = NULL;
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

void	ft_display(DIR *dirp, t_opt *opt, char *name)
{
	struct dirent	*dp;
	int				total;
	(void)name;
	(void)opt;

	total = 0;
	/*if (opt->opt_l == 1)
	{
		ft_putstr(name);
		ft_putstr(":\n");*/
		while ((dp = readdir(dirp)) != NULL)
		{
	//		if(dp->d_name[0] != '.')
	//		{
				ft_inspect_file(dp->d_name);
				ft_putendl(dp->d_name);
	//			total = ft_get_total(dp->d_name, total);
	//		}
		}
/*	}

	else
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_name[0] != '.')
				ft_putendl(dp->d_name);
		}
	if (opt->opt_l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(total);
	}*/
}
void	send_to_display(int files, t_opt *opt, char **tab)
{
	DIR *dirp;
	int i;

	i = 0;
	while (i < files)
	{
		dirp = opendir(tab[i]);
		if (dirp == NULL)
		{
			ft_errordir(tab[i]);
			exit(0);
		}
		ft_display(dirp, opt, tab[i]);
		closedir(dirp);
		i++;
	}
	if (files == 0)
	{
		dirp = opendir(".");
		ft_display(dirp, opt, "ft_ls");
		closedir(dirp);
	}
}
int		main(int ac, char **av)
{
	int				files;
	char			**tab;
	t_opt			opt;
	t_lst			l;
	
	files = 0;
	ft_init_option(&opt);
	ft_init_list(&l);
	files =	ft_parseoption(ac, av, &opt);
	tab = (char **)malloc(sizeof(char *) * (files + 1));
	ft_filesintab(ac, av, tab);
	ft_sorttab(tab, files);
	send_to_display(files, &opt, tab);
	free(tab);
	return (0);
}
