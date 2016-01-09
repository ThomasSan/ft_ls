/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:03:23 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/09 18:06:58 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_lst_display(t_lst *l, t_lst *val, t_opt *opt)
{
	l = l->next;
	if(val->next)
		val = val->next;
	while (l)
	{
		if (ft_strcmp(l->name, ".") == 0 && val->name)
		{
			printf("%s:\ntotal 0\n", val->name);
			val = val->next;
		}
		if (opt->opt_l == 1 && l->name[0] != '.')
		{
			printf("%s%5d%8s%12s%9d%13s ", l->right, l->links, l->uid, l->gid, l->size, l->time);
			if(l->is_link)
				printf("->is a link<-");
		}
		if (opt->opt_a == 1 && l->name)
			printf("%s\n", l->name);
		else if (l->name[0] != '.')
			printf("%s\n", l->name);
		l = l->next;
	}
}

void	ft_recursive_display(char *name)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(name);
	while ((dp = readdir(dirp)))
	{
		printf("%s\n", dp->d_name);
		if ()
	}
}
