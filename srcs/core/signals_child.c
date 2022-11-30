/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:13:47 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/20 18:14:00 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmp_child_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	kill(info->si_pid, SIGQUIT);
}

void	child_sig_handler(void)
{
	struct sigaction	sq;

	sq.sa_flags = SA_RESTART;
	sigemptyset(&sq.sa_mask);
	sq.sa_sigaction = tmp_child_handler;
	sigaction(SIGQUIT, &sq, NULL);
}
