/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:23:59 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/29 19:23:12 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_inspect_file(char *name)
{
    struct stat filestat;
	if(stat(name, &filestat) < 0)
        	ft_putstr("error");
	ft_putstr( (S_ISDIR(filestat.st_mode)) ? "d" : "-");
    ft_putstr( (filestat.st_mode & S_IRUSR) ? "r" : "-");
    ft_putstr( (filestat.st_mode & S_IWUSR) ? "w" : "-");
    ft_putstr( (filestat.st_mode & S_IXUSR) ? "x" : "-");
    ft_putstr( (filestat.st_mode & S_IRGRP) ? "r" : "-");
    ft_putstr( (filestat.st_mode & S_IWGRP) ? "w" : "-");
    ft_putstr( (filestat.st_mode & S_IXGRP) ? "x" : "-");
    ft_putstr( (filestat.st_mode & S_IROTH) ? "r" : "-");
    ft_putstr( (filestat.st_mode & S_IWOTH) ? "w" : "-");
    ft_putstr( (filestat.st_mode & S_IXOTH) ? "x\t" : "-\t");
	ft_putnbr(filestat.st_nlink);
	ft_putchar('\t');
	struct passwd *pwd = getpwuid(filestat.st_uid);
	ft_putstr(pwd->pw_name);
	ft_putstr("\t");
	struct group *grp = getgrgid(filestat.st_gid);
	ft_putstr(grp->gr_name);
	ft_putstr("\t");
	ft_putnbr(filestat.st_size);
	ft_putstr("\t");
	ft_print_beforelinefeed(ctime(&filestat.st_mtime));
}
