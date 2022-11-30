/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:14:50 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/19 19:09:27 by tnoulens         ###   ########.fr       */
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

int	cmpheredoc(const char *p, const char *limiter, char c)
{
	if (p == NULL && limiter == NULL)
		return (0);
	else if ((p == NULL && limiter) || (p && limiter == NULL))
		return (-1);
	else if (ft_strlen(limiter) == ft_strlen(p) - 1)
	{
		while (*p && (*p == *limiter) && *(p + 1) != c)
		{
			++p;
			++limiter;
		}
		return (*(unsigned char *)p - *(unsigned char *)limiter);
	}
	else
		return (-1);
}

int	permission(int err)
{
	if (err == 13)
		return (126);
	else if (err == 2)
		return (127);
	else
		return (err);
}
