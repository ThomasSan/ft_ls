/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <tsanzey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/27 10:58:57 by tsanzey           #+#    #+#             */
/*   Updated: 2015/12/27 11:25:44 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft/libft.h"

int		main(int ac, char **av)
{
	(void)ac;
	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(av[1]);
	if (dirp == NULL)
		return (0);
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_putendl_fd(dp->d_name, 1);
	}
	closedir(dirp);
	return (0);
}
