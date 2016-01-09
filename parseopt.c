/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseopt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 16:44:45 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/09 13:51:12 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_optionselect(char *s, t_opt *opt)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if(s[i] == 'a')
			opt->opt_a = 1;
		if(s[i] == 'l')
			opt->opt_l = 1;
		if(s[i] == 'r')
			opt->opt_r = 1;
		if(s[i] == 't')
			opt->opt_t = 1;
		if(s[i] == 'R')
			opt->opt_rec = 1;
		if(s[i] != 'R' && s[i] != 'a' && s[i] != 'l' && s[i] != 'r' && s[i] != 't')
		{
			ft_usage(s[i]);
			exit(0);
			return (-1);
		}
		i++;	
	}
	return (0);
}

void	ft_parseoption(int argc, char **argv, t_opt *opt)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			ft_optionselect(argv[i], opt);
		i++;
	}
}

void	add_name_tlst(t_lst **l, char *argv)
{
	t_lst	*new;
	t_lst	*tmp;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(argv);
	tmp = *l;
	while (tmp->next && ft_strcmp(tmp->next->name, new->name) < 0)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}

int		ft_files_to_lst(int ac, char **av, t_lst *lst)
{
	int i;
	int	files;

	i = 1;
	files = 0;
	while(i < ac)
	{
		if (ft_strncmp(av[i], "-", 1) != 0)
		{
			if (opendir(av[i]) == NULL)
				ft_errordir(av[i]);
			else
			{
				add_name_tlst(&lst, av[i]);
				files++;
			}
		}
		i++;
	}
	return (files);
}
