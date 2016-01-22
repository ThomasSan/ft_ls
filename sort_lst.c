/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 14:40:04 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/14 14:40:06 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_file_sorted(t_lst **l, t_lst *new)
{
	t_lst	*tmp;

	if (*l == NULL || ft_strcmp((*l)->name, new->name) >= 0)
	{
		new->next = *l;
		*l = new;
	}
	else
	{
		tmp = *l;
		while (tmp->next && ft_strcmp(tmp->next->name, new->name) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	add_file_rev(t_lst **l, t_lst *new)
{
	t_lst	*tmp;

	if (*l == NULL || ft_strcmp((*l)->name, new->name) <= 0)
	{
		new->next = *l;
		*l = new;
	}
	else
	{
		tmp = *l;
		while (tmp->next && ft_strcmp(tmp->next->name, new->name) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	add_file_time(t_lst **l, t_lst *new)
{
	t_lst	*tmp;

	if (*l == NULL || (*l)->date < new->date)
	{
		new->next = *l;
		*l = new;
	}
	else
	{
		tmp = *l;
		while (tmp->next && tmp->next->date > new->date)
			tmp = tmp->next;
		while (tmp->next && tmp->next->date == new->date &&
			ft_strcmp(tmp->next->name, new->name) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	add_file_time_rev(t_lst **l, t_lst *new)
{
	t_lst	*tmp;

	if (*l == NULL || (*l)->date > new->date)
	{
		new->next = *l;
		*l = new;
	}
	else
	{
		tmp = *l;
		while (tmp->next && tmp->next->date < new->date)
			tmp = tmp->next;
		while (tmp->next && tmp->next->date == new->date &&
			ft_strcmp(tmp->next->name, new->name) > 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	sort_lst(t_lst **l, t_lst *new, t_opt *opt)
{
	if (opt->opt_t == 1 && opt->opt_r == 1)
		add_file_time_rev(l, new);
	else if (opt->opt_r == 1)
		add_file_rev(l, new);
	else if (opt->opt_t == 1)
		add_file_time(l, new);
	else
		add_file_sorted(l, new);
}
