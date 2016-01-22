/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_encore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 14:58:43 by tsanzey           #+#    #+#             */
/*   Updated: 2016/01/20 14:58:44 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_pspace(char *s)
{
	ft_putstr(s);
	ft_putchar(' ');
}

size_t	ft_intlen(int n)
{
	int x;

	x = 0;
	while (n > 0)
	{
		n = n / 10;
		x++;
	}
	return (x);
}

void	ft_print_col(char *str, int col_size)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	ft_putchar(' ');
	while (i < (col_size - len))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
}

void	ft_print_col2(char *str, int col_size)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	ft_putchar(' ');
	ft_putstr(str);
	while (i < (col_size - len))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putchar(' ');
}

void	ft_print_numcol(int nb, int col_size)
{
	int	i;
	int	len;

	len = ft_intlen(nb);
	i = 0;
	ft_putchar(' ');
	if (len == 0)
		len = 1;
	while (i < (col_size - len))
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(nb);
}
