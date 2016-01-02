/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseopt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 16:44:45 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/02 17:55:16 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
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

void	ft_filesintab(int ac, char **av, char **tab)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "-", 1) == 0)
			i++;
		else
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
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
			{
				printf("strncmp est sup a 0\n");
				ft_swapstrings(&tab[i], &tab[i + 1]);
			}
			i++;
		}
		j++;
	}
}
