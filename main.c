/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/07 19:41:03 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	l->right = NULL;
	l->uid = NULL;
	l->gid = NULL;
	l->time = NULL;
	l->links = 0;
	l->size = 0;
	l->next = NULL;
}

void	ft_lst_display(t_lst *l)
{
	l = l->next;
	while (l)
	{
		printf("%s%5d%8s%12s%9d%13s ", l->right, l->links, l->uid, l->gid, l->size, l->time);
		printf("%s\n", l->name);
		l = l->next;
	}
}

void	ft_display(DIR *dirp, t_opt *opt, t_lst *l)
{
	struct dirent	*dp;
	int				total;
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
		ft_inspect_file(dp->d_name, &l);
		/*while (l)
		  {
		  l = l->next;
		  printf("name = %s\n", l->name);
		  }*/
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
void	send_to_display(int files, t_opt *opt, t_lst *val, t_lst *lst)
{
	DIR *dirp;
	int i;

	i = 0;
	printf("number of files = %d\n", files);
	while (i < files)
	{
		dirp = opendir(val->name);
		printf("Opening Dir = %s\n", val->name);
		if (dirp == NULL)
		{
			printf("Error Opening Dir\n");
			ft_errordir(val->name);
			exit(0);
		}
		ft_display(dirp, opt, lst);
		closedir(dirp);
		if (val->next)
			val = val->next;
		if (lst->next)
			lst = lst->next;
		i++;
	}
	if (files == 0)
	{
		dirp = opendir(".");
		ft_display(dirp, opt, lst);
		closedir(dirp);
	}
}
int		main(int ac, char **av)
{
	int				files;
	t_opt			opt;
	t_lst			l;
	t_lst			values;

	files = 0;
	ft_init_option(&opt);
	ft_init_list(&l);
	ft_init_list(&values);
	files =	ft_parseoption(ac, av, &opt);
	ft_files_to_lst(ac, av, &values);
	//ft_sort_list(); A implementer...
	send_to_display(files, &opt, &values, &l);
	ft_lst_display(&l);
	return (0);
}
