/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:33:49 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/14 01:55:35 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wrap_up_terminate(siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	ft_lstclear_tok(g_ms->list);
	free_param(g_ms->cm);
	clean_up(g_ms->gb, g_ms->env_array, g_ms->env);
	ft_fprintf(2, "\nTerminated\n");
	exit_fd();
	exit(143);
}

static void	wrap_up_sigpipe(siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	ft_lstclear_tok(g_ms->list);
	free_param(g_ms->cm);
	clean_up(g_ms->gb, g_ms->env_array, g_ms->env);
	exit_fd();
	exit(141);
}

void	tmp_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		g_ms->sigint = TRUE;
		g_ms->exec_ret = 130;
		if (g_ms->i.l != -1)
		{
			if (close(g_ms->cm[g_ms->i.l]->fdhd) == -1)
				perror("tmp_handler close");
			unlink(g_ms->cm[g_ms->i.l]->hdpath);
		}
		if (g_ms->pid == 0)
		{
			rl_replace_line("", 1);
			rl_on_new_line();
			write(2, "\n", 1);
			rl_redisplay();
		}
		else
			write(2, "", 1);
	}
	if (sig == SIGQUIT)
		ft_printf("\b\b");
	if (sig == SIGTERM)
		return (wrap_up_terminate(info, context), (void)0);
	if (sig == SIGPIPE)
		return (wrap_up_sigpipe(info, context), (void)0);
}

void	signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = tmp_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
	//signal(SIGPIPE, SIG_IGN);
}
