/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_and_cut.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:50:36 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/13 18:04:54 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expender(char *str, t_minishell *ms)
{
	char			*new_str;
	int				len;
	struct s_int	i;

	i.i = 0;
	i.j = 0;
	i.k = 0;
	len = 0;
	ms->i.i = 0;
	ms->i.j = 0;
	ms->i.k = 0;
	len = count_expender(i, str, ms);
	len += ft_strlen(str);
	new_str = init_expender(str, len, ms);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

int	expender_and_cut(t_minishell *minishell)
{
	char	*str;
	t_tok	*temp;

	temp = minishell->list;
	while (minishell->list)
	{
		if (minishell->list->type != 3)
		{
			str = expender(minishell->list->data, minishell);
			if (str == NULL)
				return (1);
			free (minishell->list->data);
			minishell->list->data = str;
		}
		minishell->list = minishell->list->next;
	}
	minishell->list = temp;
	if (ft_unset_tok(minishell) == 1)
		return (1);
	if (cut_quote(minishell) == 1)
		return (1);
	return (0);
}

/*void	print_tok_list(t_tok *list)
{
	t_tok *tmp;
	tmp = list;
	if (list)
	{
		while (list)
		{
			ft_printf("[%s] [%d] [%d]\n", list->data, list->type, list->infos);
			list = list->next;
		}
	}
	list = tmp;
}*/