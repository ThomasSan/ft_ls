/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:41:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/11 13:50:01 by tsanzey          ###   ########.fr       */
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
	int				dir;
	struct s_lst	*next;
}					t_lst;

/**** OPEN & READ DIRECTORIES ****/
void				ft_open_dir(char *name, t_lst *l, t_opt *opt);
void				ft_send_files(int files, t_lst *values, t_lst *l, t_opt *opt);
void				ft_inspect_dir(char *dir_name, char *str, t_lst **l, t_opt *opt);

/**** LST MANIPULATION FUNCTIONS ****/
void				test_disp(t_lst *l);
void				ft_lst_get_d(t_lst **l, t_lst **ret);
void				ft_lst_clr(t_lst **l);
void				ft_lst_clr_name(t_lst **l);
void				ft_init_option(t_opt *opt);
void				ft_parseoption(int argc, char **argv, t_opt *opt);
int					ft_files_to_lst(int ac, char **av, t_lst **lst);
t_lst				*add_name_tlst(t_lst *l, char *argv);

/**** DISPLAY ****/
void				ft_recursive_display(char *name);
void				ft_lst_display(t_lst *l, t_opt *opt);
int					ft_get_total(char *name, int blocks);

/**** MISC ****/
void				ft_usage(char c);
void				ft_errordir(char *s);
char				*cat_path(char *s1, char *s2);

#endif
