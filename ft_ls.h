/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:41:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/06 19:27:04 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct		s_opt
{
	int				opt_a;
	int				opt_l;
	int				opt_r;
	int				opt_t;
	int				opt_rec;
}					t_opt;

typedef struct		s_lst
{
	char			*name;
	char			right[10];
	char			*uid;
	char			*gid;
	char			*time;
	int				links;
	int				size;
	struct s_list	*next;
}					t_lst;

void				ft_inspect_file(t_lst *l);
void				ft_usage(char c);
void				ft_filesintab(int ac, char **av, char **tab);
void				ft_sorttab(char **tab, int files);
int					ft_parseoption(int argc, char **argv, t_opt *opt);
int					ft_get_total(char *name, int blocks);

#endif
