/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:03:40 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/20 15:03:41 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_link(char *s)
{
	char	buf[PATH_MAX];
	char	*dst;
	size_t	ret;

	if (!(ret = readlink(s, buf, PATH_MAX)))
		return (NULL);
	buf[ret] = '\0';
	dst = ft_strdup(buf);
	return (dst);
}

void	ft_minor_major(struct stat sfile, int *a, int *b)
{
	if (S_ISCHR(sfile.st_mode) || S_ISBLK(sfile.st_mode))
	{
		*a = major(sfile.st_rdev);
		*b = minor(sfile.st_rdev);
	}
}

int		ft_get_total(char *path_name, char *name, int blocks)
{
	struct stat filestat;
	char		*str_name;

	str_name = cat_path(path_name, name);
	lstat(str_name, &filestat);
	blocks = blocks + (filestat.st_blocks);
	free(str_name);
	return (blocks);
}

void	ft_usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-Rlart] [file ..]\n");
}

void	ft_errordir(char *s)
{
	ft_putstr("ft_ls: ");
	perror(s);
}
