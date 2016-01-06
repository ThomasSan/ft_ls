/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:23:59 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/06 19:27:01 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void	ft_print_beforelinefeed(char *s)
{
	int	i;

	i = 4;
	while (i < 16)
	{
		ft_putchar(s[i]);
		i++;
	}
	ft_putchar(' ');
}

void	ft_printrights(char *name)
{
	struct stat filestat;

	stat(name, &filestat);
	ft_putstr((S_ISDIR(filestat.st_mode)) ? "d" : "-");
	ft_putstr((filestat.st_mode & S_IRUSR) ? "r" : "-");
	ft_putstr((filestat.st_mode & S_IWUSR) ? "w" : "-");
	ft_putstr((filestat.st_mode & S_IXUSR) ? "x" : "-");
	ft_putstr((filestat.st_mode & S_IRGRP) ? "r" : "-");
	ft_putstr((filestat.st_mode & S_IWGRP) ? "w" : "-");
	ft_putstr((filestat.st_mode & S_IXGRP) ? "x" : "-");
	ft_putstr((filestat.st_mode & S_IROTH) ? "r" : "-");
	ft_putstr((filestat.st_mode & S_IWOTH) ? "w" : "-");
	ft_putstr((filestat.st_mode & S_IXOTH) ? "x\t" : "-\t");
}

void	ft_inspect_file(char *name, t_lst *l)
{
	struct stat filestat;
	struct passwd *pwd;
	struct group *grp;

	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	stat(name, &filestat);
	ft_printrights(name);
	// editer printrights pour la faire renvoyer une chaine a stocker dans l->right;
	ft_putnbr(filestat.st_nlink);
	l->links = filestat.st_nlink;
	ft_putchar('\t');
	ft_putstr(pwd->pw_name);
	l->uid = ft_strdup(pwd->pw_name);
	ft_putstr("\t");
	ft_putstr(grp->gr_name);
	l->gid = ft_strdup(grp->gr_name);
	ft_putstr("\t");
	ft_putnbr(filestat.st_size);
	l->size = filestat.st_size;
	ft_putstr("\t");
	ft_print_beforelinefeed(ctime(&filestat.st_mtime));
	// editer ft_print_beforelinefeed pour renvoyer la date sous une *str dans l->time;
}
/* version originale
void	ft_inspect_file(char *name)
{
	struct stat filestat;
	struct passwd *pwd;
	struct group *grp;

	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	stat(name, &filestat);
	ft_printrights(name);
	ft_putnbr(filestat.st_nlink);
	ft_putchar('\t');
	ft_putstr(pwd->pw_name);
	ft_putstr("\t");
	ft_putstr(grp->gr_name);
	ft_putstr("\t");
	ft_putnbr(filestat.st_size);
	ft_putstr("\t");
	ft_print_beforelinefeed(ctime(&filestat.st_mtime));
}
*/
int		ft_get_total(char *name, int blocks)
{
	struct stat filestat;

	stat(name, &filestat);
	blocks = blocks + (filestat.st_blocks);
	return (blocks);
}
