/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:23:59 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/07 19:41:05 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_time(char *s)
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

char	*ft_getrights(char *name)
{
	struct stat filestat;
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * 11)))
		return (NULL);
	stat(name, &filestat);
	str[0] = ((S_ISDIR(filestat.st_mode)) ? 'd' : '-');
	str[1] = ((filestat.st_mode & S_IRUSR) ? 'r' : '-');
	str[2] = ((filestat.st_mode & S_IWUSR) ? 'w' : '-');
	str[3] = ((filestat.st_mode & S_IXUSR) ? 'x' : '-');
	str[4] = ((filestat.st_mode & S_IRGRP) ? 'r' : '-');
	str[5] = ((filestat.st_mode & S_IWGRP) ? 'w' : '-');
	str[6] = ((filestat.st_mode & S_IXGRP) ? 'x' : '-');
	str[7] = ((filestat.st_mode & S_IROTH) ? 'r' : '-');
	str[8] = ((filestat.st_mode & S_IWOTH) ? 'w' : '-');
	str[9] = ((filestat.st_mode & S_IXOTH) ? 'x' : '-');
	str[10] = '\0';
	return (str);
}

void	ft_inspect_file(char *name, t_lst **l)
{
	struct stat		filestat;
	struct passwd	*pwd;
	struct group	*grp;
	t_lst			*new;
	t_lst			*tmp;

	stat(name, &filestat);
	grp = getgrgid(filestat.st_gid);
	pwd = getpwuid(filestat.st_uid);
	tmp = *l;
	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->name = ft_strdup(name);
	new->right = ft_getrights(name);
	new->links = filestat.st_nlink;
	new->uid = ft_strdup(pwd->pw_name);
	new->gid = ft_strdup(grp->gr_name);
	new->size = filestat.st_size;
	new->time = ft_get_time(ctime(&filestat.st_mtime));
	new->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		ft_get_total(char *name, int blocks)
{
	struct stat filestat;

	stat(name, &filestat);
	blocks = blocks + (filestat.st_blocks);
	return (blocks);
}
