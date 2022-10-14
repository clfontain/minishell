/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:06:24 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/14 01:08:53 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(int cmd_nbr, int *end)
{
	int	i;

	i = 0;
	while (i < cmd_nbr)
	{
		if (pipe(end + 2 * i) < 0)
			return (perror("open_pipes"), errno);
		i++;
	}
	return (0);
}

int	close_pipes(int cmd_nbr, int *end, t_command *cm)
{
	int	i;

	i = 0;
	while (i < 2 * (cmd_nbr))
	{
		if (close(end[i]) == -1)
			return (perror("close_pipes"), errno);
		i++;
	}
	if (cm->here_doc >= TRUE)
	{
		close(cm->fd[0]);
		unlink(cm->hdpath);
	}
	else if (cm->fd[0] != STDIN_FILENO)
	{
		if (close(cm->fd[0]) == -1)
			return (perror("close_std_in_child fd[0]"), errno);
	}
	if (cm->fd[1] != STDOUT_FILENO)
	{
		if (close(cm->fd[1]) == -1)
			return (perror("close_std_in_child fd[1]"), errno);
	}
	return (0);
}

int	close_pipes_parent(int cmd_nbr, int *end, t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < 2 * (cmd_nbr))
	{
		if (close(end[i]) == -1)
			return (perror("close_pipes"), errno);
		i++;
	}
	i = 0;
	while (ms->cm[i] != NULL)
	{
		if (ms->cm[i]->fd[0] != STDIN_FILENO)
		{
			if (close(ms->cm[i]->fd[0]) == -1)
				return (perror("close_pipes"), errno);
		}
		if (ms->cm[i]->fd[1] != STDOUT_FILENO)
		{
			if (close(ms->cm[i]->fd[1]) == -1)
				return (perror("close_pipes"), errno);
		}
		i++;
	}
	return (0);
}

void	dupper(int input, int output, t_minishell *ms, int i)
{
	if (ms->cm[i]->fd[0] != STDIN_FILENO)
		input = ms->cm[i]->fd[0];
	if (dup2(input, STDIN_FILENO) == -1)
		return (perror("dupper input"), (void)0);
	if (ms->cm[i]->fd[1] != STDOUT_FILENO)
		output = ms->cm[i]->fd[1];
	if (dup2(output, STDOUT_FILENO) == -1)
		return (perror("dupper output"), (void)0);
}

void	close_std_in_child(t_minishell *ms)
{
	int	j;

	if (close(0) == -1)
		return (perror("close_std_in_child"), (void)0);
	if (close(1) == -1)
		return (perror("close_std_in_child"), (void)0);
	if (close(2) == -1)
		return (perror("close_std_in_child"), (void)0);
	j = 0;
	while (ms->cm[j] != NULL)
	{
		if (ms->cm[j]->fd[1] != STDOUT_FILENO)
		{
			if (close(ms->cm[j]->fd[1]) == -1)
				return (perror("close_std_in_child while loop"), (void)0);
		}
		j++;
	}
}
