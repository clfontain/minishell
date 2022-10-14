/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:14:50 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/13 18:53:52 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_to_cmd(t_command **cm, int i)
{
	t_list	*tmp;
	size_t	idx;

	if (cm[i]->cmd != NULL)
		free(cm[i]->cmd);
	idx = ft_lstsize(cm[i]->cmdlst);
	cm[i]->cmd = (char **)ft_calloc(sizeof(char *), idx + 1);
	if (!cm[i]->cmd)
		return (perror("list_to_cmd"), -1);
	tmp = cm[i]->cmdlst;
	idx = 0;
	while (tmp != NULL)
	{
		cm[i]->cmd[idx] = tmp->content;
		idx++;
		tmp = tmp->next;
	}
	return (0);
}

void	init_int(t_minishell *ms, t_int *i)
{
	i->i = 0;
	i->j = 0;
	i->k = 0;
	ms->i.i = 0;
	ms->i.j = 0;
	ms->i.k = 0;
}
