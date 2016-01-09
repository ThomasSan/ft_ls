/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/09 18:07:00 by tsanzey          ###   ########.fr       */
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
}

void	ft_open_dir(int files, t_lst *val, t_lst *lst)
{
	DIR *dirp;
	int i;

	i = 0;
	while (i < files)
	{
		if (val->next)
			val = val->next;
		dirp = opendir(val->name);
		if (dirp == NULL)
		{
			ft_errordir(val->name);
			exit(0);
		}
		ft_read_dir(dirp, lst);
		closedir(dirp);
		i++;
	}
	if (files == 0)
	{
		dirp = opendir(".");
		ft_read_dir(dirp, lst);
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
	ft_parseoption(ac, av, &opt);
	files =	ft_files_to_lst(ac, av, &values);
	ft_open_dir(files, &values, &l);
	if (opt.opt_rec == 1)
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
	return (0);
}
