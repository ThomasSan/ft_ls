/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:18:07 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/20 15:18:11 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursive_option(t_lst *l, t_opt *opt, char *name)
{
	t_lst			*ret;

	ret = NULL;
	ft_lst_get_d(&l, &ret);
	ft_lst_clr(&l);
	while (ret)
	{
		ft_putchar('\n');
		ft_putstr(cat_path(name, ret->name));
		ft_putendl(":");
		ft_open_dir(cat_path(name, ret->name), l, opt);
		ret = ret->next;
	}
	ft_lst_clr(&ret);
}

void	ft_read_dir(DIR *dirp, t_lst *l, t_opt *opt, char *name)
{
	struct dirent	*dp;

	while ((dp = readdir(dirp)) != NULL)
	{
		opt->is_dir = 1;
		if (opt->opt_a == 1)
		{
			opt->total = ft_get_total(name, dp->d_name, opt->total);
			ft_inspect_dir(name, dp->d_name, &l, opt);
		}
		else if (ft_strncmp(dp->d_name, ".", 1) != 0)
		{
			opt->total = ft_get_total(name, dp->d_name, opt->total);
			ft_inspect_dir(name, dp->d_name, &l, opt);
		}
	}
	ft_lst_display(l, opt);
	opt->total = 0;
	if (opt->opt_rec == 1)
	{
		recursive_option(l, opt, name);
	}
}

void	ft_open_dir(char *name, t_lst *l, t_opt *opt)
{
	DIR			*dirp;
	struct stat	filestat;

	dirp = opendir(name);
	if (dirp == NULL)
	{
		if (lstat(name, &filestat) == 0 && errno != 2 && errno != 13)
		{
			ft_inspect_file(name, &l, opt);
			ft_lst_display(l, opt);
			ft_lst_clr(&l);
		}
		else
			ft_errordir(name);
	}
	else
	{
		ft_read_dir(dirp, l, opt, name);
		closedir(dirp);
	}
}

void	ft_send_files(int files, t_lst *values, t_lst *l, t_opt *opt)
{
	while (values)
	{
		ft_open_dir(values->name, l, opt);
		values = values->next;
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

	l = NULL;
	values = NULL;
	ft_init_option(&opt);
	ft_parseoption(ac, av, &opt);
	files = ft_files_to_lst(ac, av, &values);
	ft_send_files(files, values, l, &opt);
	ft_lst_clr_name(&values);
	return (0);
}
