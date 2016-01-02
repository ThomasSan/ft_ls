/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:41:06 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/02 17:41:06 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct		s_opt
{
	char			*name;
	int				opt_a;
	int				opt_l;
	int				opt_r;
	int				opt_t;
	int				opt_rec;
}					t_opt;

void				ft_inspect_file(char *name);
void				ft_usage(char c);
void				ft_filesintab(int ac, char **av, char **tab);
void				ft_sorttab(char **tab, int files);
int					ft_parseoption(int argc, char **argv, t_opt *opt);

#endif
