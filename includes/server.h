/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouflet <amouflet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:56:41 by amouflet          #+#    #+#             */
/*   Updated: 2023/01/10 15:46:08 by amouflet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_char
{
	int				c;
	struct s_char	*next;
}t_char;

void	free_lst(t_char *lst);
int		check_final_byte(int c);
void	print_list(t_char *lst);
t_char	*add(int c);
void	ft_putnbr_fd(int n, int fd);
int		save_char(t_char **tmp, int *c, siginfo_t *info);

#endif /*SERVER_H*/