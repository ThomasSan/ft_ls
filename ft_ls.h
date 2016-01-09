/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:41:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/09 17:56:38 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

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
	char			*right;
	char			*uid;
	char			*gid;
	char			*time;
	int				links;
	int				size;
	int				is_link;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_names
{
	char			*name;
	struct s_names	*next;
}					t_names;

void				ft_recursive_display(char *name);
void				ft_lst_display(t_lst *l, t_lst *val, t_opt *opt);
void				ft_init_list(t_lst *l);
void				ft_init_option(t_opt *opt);
void				ft_inspect_file(char *str, t_lst **l);
void				ft_usage(char c);
void				ft_sorttab(char **tab, int files);
void				ft_errordir(char *s);
void				ft_firstfile(char *name, t_lst *lst);
void				ft_parseoption(int argc, char **argv, t_opt *opt);
int					ft_files_to_lst(int ac, char **av, t_lst *lst);
int					ft_get_total(char *name, int blocks);

#endif
