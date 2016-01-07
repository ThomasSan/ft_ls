/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseopt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 16:44:45 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/07 19:19:36 by tsanzey          ###   ########.fr       */
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

int		ft_parseoption(int argc, char **argv, t_opt *opt)
{
	int	i;
	int	files;

	i = 1;
	files = 0;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			ft_optionselect(argv[i], opt);
		else
			files++;
		i++;
	}
	return (files);
}

void	add_name_tlst(t_lst **l, char *argv)
{
	t_lst	*new;
	t_lst	*tmp;

	tmp = *l;
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(argv);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	printf("name is = %s\n", new->name);
	new->next = NULL;
}

void	ft_files_to_lst(int ac, char **av, t_lst *lst)
{
	int i;

	i = 1;
	while(i < ac)
	{
		if (ft_strncmp(av[i], "-", 1) != 0)
		{
			if (opendir(av[i]) == NULL)
				ft_errordir(av[i]);
			else
				add_name_tlst(&lst, av[i]);
		}
		i++;
	}
}

void	ft_swapstrings(char **s1, char **s2)
{
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp1 = *s1;
	tmp2 = *s2;
	tmp = ft_strdup(*s1);
	*s1 = ft_strdup(*s2);
	*s2 = ft_strdup(tmp);
	free(tmp);
	free(tmp1);
	free(tmp2);
}

void	ft_sorttab(char **tab, int files)
{
	int	i;
	int	j;

	j = 0;
	while (j < files - 1)
	{
		i = 0;
		while (i < files - 1)
		{
			if (ft_strncmp(tab[i], tab[i + 1], 1) > 0)
				ft_swapstrings(&tab[i], &tab[i + 1]);
			i++;
		}
		j++;
	}
}
