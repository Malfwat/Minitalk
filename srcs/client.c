/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:45:52 by amouflet          #+#    #+#             */
/*   Updated: 2023/03/28 16:03:01 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "client.h"

int	g_open;

void	handler(int num)
{
	(void)num;
	g_open = GO;
}

void	end(int num)
{
	(void)num;
	g_open = LEAVE;
}

void	send_next_char(int pid, char c)
{
	int	bit;
	int	tmp;

	bit = 8;
	while (bit > 0)
	{
		if (g_open == GO)
		{
			g_open = WAIT;
			if (c >> (bit - 1) & 1)
				tmp = kill(pid, SIGUSR1);
			else
				tmp = kill(pid, SIGUSR2);
			if (tmp == -1)
			{
				write(2, "Wrong PID!\n", 12);
				exit(0);
			}
			bit--;
		}
	}
}

struct sigaction	init(int *pid, char **av)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sb.sa_handler = &end;
	sb.sa_flags = SA_SIGINFO;
	sigemptyset(&sb.sa_mask);
	sigaction(SIGUSR1, &sb, NULL);
	*pid = atoi(av[1]);
	return (sa);
}

int	main(int ac, char **av)
{
	int					pid;
	int					i;

	if (ac != 3)
		return (write(1, "./client PID Message\n", 22), 0);
	i = 0;
	g_open = GO;
	init(&pid, av);
	while (av[2][i])
		send_next_char(pid, av[2][i++]);
	send_next_char(pid, '\n');
	send_next_char(pid, '\0');
	while (g_open != LEAVE)
		usleep(10);
	return (0);
}
