/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:03:23 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/20 15:17:31 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_colsize(t_opt *opt, t_lst *l)
{
	t_lst *tmp;

	tmp = l;
	opt->len_name = 0;
	opt->len_grp = 0;
	opt->len_link = 0;
	opt->len_size = 0;
	while (tmp)
	{
		if (opt->len_name == 0 || ft_strlen(tmp->uid) > opt->len_name)
			opt->len_name = ft_strlen(tmp->uid);
		if (opt->len_grp == 0 || ft_strlen(tmp->gid) > opt->len_grp)
			opt->len_grp = ft_strlen(tmp->gid);
		if (opt->len_link == 0 || ft_intlen(tmp->links) > opt->len_link)
			opt->len_link = ft_intlen(tmp->links);
		if (opt->len_size == 0 || ft_intlen(tmp->size) > opt->len_size)
			opt->len_size = ft_intlen(tmp->size);
		if (opt->len_major == 0 || ft_intlen(tmp->major) > opt->len_major)
			opt->len_major = ft_intlen(tmp->major);
		if (opt->len_minor == 0 || ft_intlen(tmp->minor) > opt->len_minor)
			opt->len_minor = ft_intlen(tmp->minor);
		tmp = tmp->next;
	}
}

void	ft_display_long(t_lst *l, t_opt *opt)
{
	ft_get_colsize(opt, l);
	while (l)
	{
		ft_putstr(l->right);
		ft_print_numcol(l->links, opt->len_link + 1);
		ft_print_col2(l->uid, opt->len_name);
		ft_print_col2(l->gid, opt->len_grp);
		if (l->right[0] == 'c' || l->right[0] == 'b')
		{
			ft_print_numcol(l->major, opt->len_major);
			ft_print_numcol(l->minor, opt->len_minor);
		}
		else
			ft_print_numcol(l->size, opt->len_size);
		ft_print_col(l->time, 2);
		ft_putstr(" ");
		ft_putstr(l->name);
		if (l->is_link)
		{
			ft_putstr(" -> ");
			ft_putstr(l->symlink);
		}
		ft_putchar('\n');
		l = l->next;
	}
}

void	ft_lst_display(t_lst *l, t_opt *opt)
{
	if (opt->opt_l == 1)
	{
		if (opt->is_dir == 1)
		{
			ft_putstr("total ");
			ft_putnbr(opt->total);
			ft_putchar('\n');
		}
		ft_display_long(l, opt);
	}
	else
		while (l)
		{
			ft_putstr(l->name);
			ft_putchar('\n');
			l = l->next;
		}
}
