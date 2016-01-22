/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:23:59 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/20 15:03:32 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_time(char *s, t_lst *new)
{
	char	*str;
	int		i;
	int		j;

	i = 4;
	j = 0;
	if (!(str = (char *)malloc(sizeof(char) * 13)))
		return (NULL);
	if (((int)time(NULL) - new->date > 31536000) ||
			((int)time(NULL) - new->date < -31536000))
	{
		while (i < 11)
			str[j++] = s[i++];
		str[j++] = ' ';
		i = 20;
		while (i < 24)
			str[j++] = s[i++];
	}
	while (i < 16)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

char	filetype(int mode, t_lst *l)
{
	char c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	l->is_link = (c == 'l') ? 1 : 0;
	l->dir = (c == 'd') ? 1 : 0;
	return (c);
}

char	*ft_getrights(int mode, t_lst *l)
{
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx",
		"r--", "r-x", "rw-", "rwx"};
	char				*bits;

	if (!(bits = (char *)malloc(sizeof(char) * 11)))
		return (NULL);
	bits[0] = filetype(mode, l);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXUSR) ? 't' : 'T';
	bits[10] = '\0';
	return (bits);
}

void	ft_inspect_dir(char *path_name, char *name, t_lst **l, t_opt *opt)
{
	struct stat		filestat;
	struct passwd	*pwd;
	struct group	*grp;
	char			*dir;
	t_lst			*new;

	dir = cat_path(path_name, name);
	lstat(dir, &filestat);
	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(name);
	new->right = ft_getrights(filestat.st_mode, new);
	new->links = filestat.st_nlink;
	new->uid = pwd ? ft_strdup(pwd->pw_name) : NULL;
	new->gid = grp ? ft_strdup(grp->gr_name) : NULL;
	new->size = filestat.st_size;
	ft_minor_major(filestat, &new->major, &new->minor);
	new->date = filestat.st_mtime;
	new->time = ft_get_time(ctime(&filestat.st_mtime), new);
	new->symlink = new->is_link ? ft_get_link(dir) : NULL;
	sort_lst(l, new, opt);
	free(dir);
}

void	ft_inspect_file(char *name, t_lst **l, t_opt *opt)
{
	struct stat		filestat;
	struct passwd	*pwd;
	struct group	*grp;
	t_lst			*new;

	lstat(name, &filestat);
	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(name);
	new->right = ft_getrights(filestat.st_mode, new);
	new->links = filestat.st_nlink;
	new->uid = pwd ? ft_strdup(pwd->pw_name) : NULL;
	new->gid = grp ? ft_strdup(grp->gr_name) : NULL;
	new->size = filestat.st_size;
	new->date = filestat.st_mtime;
	new->time = ft_get_time(ctime(&filestat.st_mtime), new);
	new->symlink = new->is_link ? ft_get_link(name) : NULL;
	sort_lst(l, new, opt);
}
