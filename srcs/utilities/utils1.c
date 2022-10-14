/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:28:09 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/05 22:20:57 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fd_in(t_command *cm)
{
	if (cm->here_doc >= TRUE)
	{
		cm->fd[0] = open(".here_doc.tmp", O_RDONLY);
		if (cm->fd[0] == -1 || cm->fd[0] > FOPEN_MAX)
			perror("get_fd_in");
	}
}

int	nb_cmd(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return (0);
	else
	{
		while (argv[i])
			i++;
	}
	return (i);
}

void	list_to_array(t_minishell *ms)
{
	t_list	*tmp;
	size_t	idx;

	if (ms->env_array != NULL)
		free(ms->env_array);
	idx = ft_lstsize(ms->env);
	ms->env_array = (char **)ft_calloc(sizeof(char *), idx + 1);
	if (!ms->env_array)
		return (perror("list_to_array"), (void)0);
	tmp = ms->env;
	idx = 0;
	while (tmp != NULL)
	{
		ms->env_array[idx] = tmp->content;
		idx++;
		tmp = tmp->next;
	}
}

void	list_to_export(t_minishell *ms)
{
	t_list	*tmp;
	size_t	idx;

	if (ms->env_array != NULL)
		free(ms->env_array);
	idx = ft_lstsize(ms->env);
	ms->env_array = (char **)ft_calloc(sizeof(char *), idx + 1);
	if (!ms->env_array)
		return (perror("list_to_array"), (void)0);
	tmp = ms->env;
	idx = 0;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->content, '='))
		{
			ms->env_array[idx] = tmp->content;
			idx++;
		}
		tmp = tmp->next;
	}
}

void	child_exit(t_minishell *ms)
{
	close_std_in_child(ms);
	clean_up(ms->gb, ms->env_array, ms->env);
	ft_lstclear_tok(ms->list);
	free_param(ms->cm);
	exit(ms->exec_ret);
}
