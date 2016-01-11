/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:03:36 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/11 12:16:17 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	ft_lst_clr(t_lst **l)
{
	t_lst	*tmp;
	t_lst	*to_free;

	tmp = *l;
	while (tmp)
	{
		to_free = tmp; 
		tmp = tmp->next;
		free(to_free);
	}
	*l = NULL;
}
