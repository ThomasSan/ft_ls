/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/11 13:50:54 by tsanzey          ###   ########.fr       */
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

void	ft_read_dir(DIR *dirp, t_lst *l)
{
	struct dirent	*dp;
	int				total;

	total = 0;
	while ((dp = readdir(dirp)) != NULL)
		ft_inspect_file(dp->d_name, &l);
	test_disp(l);
}

void	ft_open_dir(int files, char *name, t_lst *lst)
{
	DIR *dirp;

	if (files == 0)
	{
		dirp = opendir(".");
		ft_read_dir(dirp, lst);
	}
	else
	{
		dirp = opendir(name);
		if (dirp == NULL)
		{
			printf("name = %s\n", name);
			ft_errordir(name);
			exit(0);
		}
		ft_read_dir(dirp, lst);
	}
	closedir(dirp);
}

void	test_disp(t_lst *l)
{
	if (l == NULL)
		printf("Linked List is \033[31mEMPTY\033[0m\n");
	while (l)
	{
		printf("%s\n", l->name);
		l = l->next;
	}
}
int		main(int ac, char **av)
{
	int				files;
	t_opt			opt;
	t_lst			*l;
	t_lst			*values;

	files = 0;
	l = NULL;
	values =NULL;
	ft_init_option(&opt);
	ft_parseoption(ac, av, &opt);
	files =	ft_files_to_lst(ac, av, &values);
	printf("files = %d, values->name = %s\n", files, values->name);
	while (values)
	{
		printf("%s :\ntotal 0\n", values->name);//define total later
		ft_open_dir(files, values->name, l);
		values = values->next;
		printf("\n");
	}
	/*if (opt.opt_rec == 1)
	{
		values = *values.next;
		while (values.name)
		{
			ft_recursive_display(values.name);
			values = *values.next;
		}
	}
	else
		ft_lst_display(&l, &values, &opt);
	ft_lst_clr(&values);*/
	ft_lst_clr(&values);
	return (0);
}
