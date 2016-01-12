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

//Implementer une Sorted_LST pour cette function
void	ft_lst_get_d(t_lst **l, t_lst **ret)
{
	t_lst	*tmp;

	tmp = *l;
	while (tmp)
	{
		if (tmp->dir == 1 && ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0)
		{
			/*tmp1 = *ret;
			if(!(new = (t_lst*)malloc(sizeof(t_lst))))
				return ;
			new->name = ft_strdup(tmp->name);
			new->next = NULL;
			if (ret == NULL, ft_strcmp(l->name, new->name))
			{
				*ret = new;
			}
			else
			{
				while (tmp1->next)
					tmp1 = tmp1->next;
				tmp1->next = new;
			}*/
			*ret = add_name_tlst(*ret, tmp->name);
		}
		tmp = tmp->next;
	}
}

char	*cat_path(char *s1, char *s2)
{
	char	*dst;
	int		len;
 	int		i;
 	int		j;

 	i = 0;
 	j = 0;
 	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dst = (char *)malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '/';
	i++;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}