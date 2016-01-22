/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:41:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/21 18:29:57 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct		s_opt
{
	int				opt_a;
	int				opt_l;
	int				opt_r;
	int				opt_t;
	int				opt_rec;
	int				total;
	int				is_dir;
	size_t			len_name;
	size_t			len_grp;
	size_t			len_link;
	size_t			len_size;
	size_t			len_major;
	size_t			len_minor;
}					t_opt;

typedef struct		s_lst
{
	char			*name;
	char			*right;
	char			*uid;
	char			*gid;
	char			*time;
	char			*symlink;
	int				major;
	int				minor;
	int				links;
	int				size;
	int				is_link;
	int				dir;
	int				date;
	struct s_lst	*next;
}					t_lst;

void				ft_open_dir(char *name, t_lst *l, t_opt *opt);
void				ft_send_files(int files, t_lst *val, t_lst *l, t_opt *opt);
void				ft_inspect_dir(char *s1, char *s2, t_lst **l, t_opt *opt);
void				ft_inspect_file(char *name, t_lst **l, t_opt *opt);
char				*ft_get_link(char *s);
void				ft_minor_major(struct stat sfile, int *a, int *b);
int					ft_get_total(char *path_name, char *name, int blocks);

void				ft_lst_get_d(t_lst **l, t_lst **ret);
void				ft_lst_clr(t_lst **l);
void				ft_lst_clr_name(t_lst **l);
void				ft_init_option(t_opt *opt);
void				ft_parseoption(int argc, char **argv, t_opt *opt);
int					ft_files_to_lst(int ac, char **av, t_lst **lst);
t_lst				*add_name_tlst(t_lst *l, char *argv);

void				sort_lst(t_lst **l, t_lst *new, t_opt *opt);

void				ft_get_colsize(t_opt *opt, t_lst *l);
void				ft_recursive_display(char *name);
void				ft_lst_display(t_lst *l, t_opt *opt);
int					ft_get_total(char *s, char *name, int blocks);

void				ft_usage(char c);
void				ft_errordir(char *s);
char				*cat_path(char *s1, char *s2);
void				ft_put_pspace(char *s);
size_t				ft_intlen(int n);
void				ft_print_col(char *str, int col_size);
void				ft_print_col2(char *str, int col_size);
void				ft_print_numcol(int nb, int col_size);

#endif
