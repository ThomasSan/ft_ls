/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:23:59 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/11 11:43:03 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_get_time(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 4;
	j = 0;
	if(!(str = (char *)malloc(sizeof(char) * 13)))
		return (NULL);
	while (i < 16)
	{
		str[j] = s[i];
		i++;
		j++;
	}
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
    return(c);
}

char	*ft_getrights(int mode, t_lst *l)
{
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx",
    "r--", "r-x", "rw-", "rwx"};
    char			*bits;

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

void		ft_inspect_file(char *name, t_lst **l)
{
	struct stat		filestat;
	struct passwd	*pwd;
	struct group	*grp;
	t_lst			*new;
	t_lst			*tmp;

	lstat(name, &filestat);
	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	// printf("filestat.mode = %d\n", filestat.st_mode);
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(name);
	new->right = ft_getrights(filestat.st_mode, new);
	new->links = filestat.st_nlink;
	new->uid = ft_strdup(pwd->pw_name);
	new->gid = ft_strdup(grp->gr_name);
	new->size = filestat.st_size;
	new->time = ft_get_time(ctime(&filestat.st_mtime));
	if (*l == NULL || ft_strcmp((*l)->name, new->name) >= 0)
	{
		new->next = *l;
		*l = new;
	}
	else
	{
		tmp = *l;
		while (tmp->next && ft_strcmp(tmp->next->name, new->name) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

int			ft_get_total(char *name, int blocks)
{
	struct stat filestat;

	stat(name, &filestat);
	blocks = blocks + (filestat.st_blocks);
	return (blocks);
}
