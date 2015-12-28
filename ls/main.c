/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/28 14:09:53 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include "ft_ls.h"

int		ft_parse_option()
{
	
	return (0);
}

int		main(int ac, char **av)
{
	(void)ac;
	DIR *dirp;
	struct dirent *dp;

	if (ac == 1)
		dirp = opendir(".");
	else
		dirp = opendir(av[1]);
	if (dirp == NULL)
		return (0);
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_inspect_file(dp->d_name);
		ft_putendl(dp->d_name);
	}
	closedir(dirp);
	return (0);
}
