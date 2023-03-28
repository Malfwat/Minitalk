/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:28:59 by amouflet          #+#    #+#             */
/*   Updated: 2023/01/10 15:46:32 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_char	*g_head;

void	free_lst(t_char *lst)
{
	t_char	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

int	add_back(t_char **tmp, int c)
{
	if (!(*tmp))
	{
		(*tmp) = add(c);
		if (!(*tmp))
			return (0);
	}
	else
	{
		(*tmp)->next = add(c);
		if (!(*tmp)->next)
		{
			free_lst(g_head);
			exit (0);
		}
		(*tmp) = (*tmp)->next;
	}
	return (1);
}

int	save_char(t_char **tmp, int *c, siginfo_t *info)
{
	add_back(tmp, *c);
	if (g_head == NULL)
		g_head = *tmp;
	if (check_final_byte(*c))
	{
		kill(info->si_pid, SIGUSR1);
		print_list(g_head);
		*tmp = NULL;
		g_head = NULL;
	}
	*c = 0;
	return (0);
}

void	get_bit(int num, siginfo_t *info)
{
	static int		count;
	static int		c;
	static t_char	*tmp;

	if (count == 0 && c != 0)
		c = 0;
	if (num == SIGUSR1)
		c = c * 2 + 1;
	else if (num == SIGUSR2)
		c = c * 2 + 0;
	count++;
	if (count == 8)
		count = save_char(&tmp, &c, info);
	kill(info->si_pid, SIGUSR2);
	return ;
}

int	main(void)
{
	struct sigaction	sa;

	g_head = NULL;
	sa.sa_sigaction = (void *)get_bit;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		sleep(1);
	return (0);
}
