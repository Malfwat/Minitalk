/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:17:18 by amouflet          #+#    #+#             */
/*   Updated: 2023/01/10 15:37:44 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 2147483647)
		write(fd, "2147483647", 10);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		c = (n % 10 + '0');
		write(fd, &c, 1);
	}
}

int	check_final_byte(int c)
{
	int	bit;

	bit = 8;
	while (bit > 0)
	{
		if (c >> (bit - 1) & 1)
			return (0);
		bit--;
	}
	return (1);
}

t_char	*add(int c)
{
	t_char	*new;

	new = malloc(sizeof(t_char));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void	print_list(t_char *lst)
{
	t_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		write(1, &tmp->c, 1);
		tmp = tmp->next;
	}
	free_lst(lst);
}
