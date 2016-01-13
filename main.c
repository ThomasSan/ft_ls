/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/13 15:08:52 by tsanzey          ###   ########.fr       */
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

void	ft_read_dir(DIR *dirp, t_lst *l, t_opt *opt, char *name)
{
	struct dirent	*dp;
	int				total;
	t_lst			*ret;

	total = 0;
	while ((dp = readdir(dirp)) != NULL)
		ft_inspect_file(name, dp->d_name, &l);
	ft_lst_display(l, opt);
	printf("\n");
	if (opt->opt_rec == 1)
	{
		ft_lst_get_d(&l, &ret);
		ft_lst_clr(&l);
		while (ret)
		{
			ft_open_dir(cat_path(name, ret->name), l, opt);
			ret = ret->next;
		}
	}
	ft_lst_clr(&l);
}

void	ft_open_dir(char *name, t_lst *l, t_opt *opt)
{
	DIR		*dirp;

	dirp = opendir(name);
	if (dirp == NULL)
	{
		ft_errordir(name);
		exit(0);
	}
	ft_read_dir(dirp, l, opt, name);
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

void	ft_send_files(int files, t_lst *values, t_lst *l, t_opt *opt)
{
	while (values)
	{
		if (opt->opt_l == 1)
			printf("total 0\n");//define total later
		ft_open_dir(values->name, l, opt);
		values = values->next;
		// printf("\n");
	}
	if (files == 0)
		ft_open_dir(".", l, opt);
}

int		main(int ac, char **av)
{
	int				files;
	t_opt			opt;
	t_lst			*l;
	t_lst			*values;

	files = 0;
	l = NULL;
	values = NULL;
	ft_init_option(&opt);
	ft_parseoption(ac, av, &opt);
	files =	ft_files_to_lst(ac, av, &values);
	ft_send_files(files, values, l, &opt);
	ft_lst_clr(&values);
	return (0);
}
