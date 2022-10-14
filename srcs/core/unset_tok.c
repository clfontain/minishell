/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfontain <cfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:44:18 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/06 14:02:08 by cfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_export_tok(t_minishell *ms)
{
	t_tok	*tmp;
	size_t	idx;
	char	**empty_str;

	idx = ft_lstsize_tok(ms->list);
	empty_str = (char **)ft_calloc(sizeof(char *), idx + 1);
	if (!empty_str)
		return (perror("list_to_export_tok"), NULL);
	tmp = ms->list;
	idx = 0;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->data, '\0'))
		{
			empty_str[idx] = tmp->data;
			idx++;
		}
		tmp = tmp->next;
	}
	return (empty_str);
}

static int	find_idx_tok(t_tok *tok, char *arg)
{
	int		i;
	t_tok	*p;

	(void)arg;
	i = 0;
	p = tok;
	while (p)
	{
		if (ft_strchr(p->data, 0) == p->data)
			return (i);
		p = p->next;
		i++;
	}
	return (-1);
}

static void	del_idx_0_tok(t_minishell *ms)
{
	t_tok	*tmp;

	tmp = ms->list;
	ms->list = ms->list->next;
	free(tmp->data);
	free(tmp);
}

static void	del_idx_pos_tok(t_minishell *ms, int idx)
{
	t_tok	*tmp;
	t_tok	*tmp2;

	tmp2 = ms->list;
	while (idx--)
	{
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
	tmp->next = tmp2->next;
	free(tmp2->data);
	free(tmp2);
}

int	ft_unset_tok(t_minishell *ms)
{
	int		i;
	int		idx;
	char	**argv;

	argv = list_to_export_tok(ms);
	if (argv == NULL)
		return (1);
	i = 0;
	while (argv[i] != NULL)
	{
		idx = find_idx_tok(ms->list, argv[i]);
		if (idx == -1)
		{
			i++;
			continue ;
		}
		if (idx == 0)
			del_idx_0_tok(ms);
		else if (idx > 0)
			del_idx_pos_tok(ms, idx);
		i++;
	}
	free(argv);
	return (SUCCESS);
}
