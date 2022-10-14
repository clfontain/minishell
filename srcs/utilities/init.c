/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:57:27 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/14 01:45:35 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_ms;

void	init_builtin(t_builtin *built)
{	
	ft_strlcpy(built[0].name, "echo", 5);
	ft_strlcpy(built[1].name, "env", 4);
	ft_strlcpy(built[2].name, "exit", 5);
	ft_strlcpy(built[3].name, "export", 7);
	ft_strlcpy(built[4].name, "pwd", 4);
	ft_strlcpy(built[5].name, "unset", 6);
	ft_strlcpy(built[6].name, "cd", 3);
	built[0].func = ft_echo;
	built[1].func = ft_env;
	built[2].func = ft_exit;
	built[3].func = ft_export;
	built[4].func = ft_pwd;
	built[5].func = ft_unset;
	built[6].func = ft_cd;
}

void	init_minishell(t_minishell *minishell, int argc, char **envp)
{
	(void)argc;
	if (argc == 1)
		print_welcome_msg(envp);
	g_ms = minishell;
	minishell->nbr_cmd = 1;
	minishell->cm = NULL;
	minishell->cmd_array = NULL;
	minishell->exec_ret = 0;
	minishell->gb = NULL;
	minishell->env = NULL;
	minishell->env_array = NULL;
	minishell->list = NULL;
	minishell->sigint = FALSE;
	minishell->i.i = -1;
	minishell->pid = 0;
}

void	init_struct(t_minishell *ms, t_command *cm)
{
	cm->cmd = NULL;
	cm->cmdlst = NULL;
	cm->fd[0] = STDIN_FILENO;
	cm->fd[1] = STDOUT_FILENO;
	cm->fdhd = -1;
	cm->hdpath = NULL;
	cm->here_doc = FALSE;
	cm->limiter = NULL;
	cm->inf = NULL;
	cm->o = NULL;
	cm->env = ms->env_array;
	cm->sigint = ms->sigint;
}

void	mini_init(t_minishell *ms)
{
	ms->nbr_cmd = 1;
	ms->list = NULL;
	ms->gb = NULL;
	ms->cm = NULL;
	ms->pid = 0;
	ms->i.l = -1;
}
