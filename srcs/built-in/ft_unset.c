/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:50:10 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/13 16:17:21 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_idx(t_list *lst, char *arg)
{
	int		i;
	t_list	*p;

	i = 0;
	p = lst;
	while (p)
	{
		if (ft_cmpchr(p->content, arg, '=') == 0)
			return (i);
		p = p->next;
		i++;
	}
	return (-1);
}

static void	del_idx_0(t_minishell *ms)
{
	t_list	*tmp;

	tmp = ms->env;
	ms->env = ms->env->next;
	free(tmp->content);
	free(tmp);
}

static void	del_idx_pos(t_minishell *ms, int idx)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp2 = ms->env;
	while (idx--)
	{
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
	tmp->next = tmp2->next;
	free(tmp2->content);
	free(tmp2);
}

int	ft_unset(t_minishell *ms, int argc, char **argv)
{
	int		i;
	int		idx;

	if (argc == 1)
		return (SUCCESS);
	i = 1;
	while (argv[i] != NULL)
	{
		idx = find_idx(ms->env, argv[i]);
		if (idx == 0)
			del_idx_0(ms);
		else if (idx > 0)
			del_idx_pos(ms, idx);
		i++;
	}
	list_to_export(ms);
	return (SUCCESS);
}
